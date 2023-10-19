#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

namespace {

struct SkeletonPass : public PassInfoMixin<SkeletonPass> {
  //  Key Points Detection (Goal 1):
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    std::map<std::string, std::tuple<std::string, int, int>> branchDictionary;

    int branchNumber = 0;

    for (Function &F : M) {
      if (F.isDeclaration()) {
        continue;
      }

      bool flag = false;
      for (BasicBlock &BB : F) {
        for (Instruction &I : BB) {
          if (auto *BI = dyn_cast<BranchInst>(&I)) {
              int numSuccessors = BI->getNumSuccessors();
              for (int i = 0; i < numSuccessors; ++i) {
                BasicBlock *branch = BI->getSuccessor(i);
                std::string opcodeName = BI->getOpcodeName();
                std::string branchID = opcodeName + "_" + std::to_string(branchNumber);
                std::string fileName = F.getParent()->getSourceFileName();

                int lineNumber = BI->getDebugLoc().getLine();
                int targetLine = branch->getFirstNonPHI()->getDebugLoc().getLine();
                branchDictionary[branchID] = std::make_tuple(fileName, lineNumber, targetLine);
                branchNumber += 1;
                flag = true;
              }
          }
        }
      }
      if (flag) {
        errs() << F.getName() << ": func_" << &F << "\n";
        flag = false;
      }
    }

    errs() << "Dictionary: " << "\n";
    for (const auto &entry : branchDictionary) {
      const std::string &branchID = entry.first;
      const std::tuple<std::string, int, int> &location = entry.second;
      errs() << branchID << ": " << std::get<0>(location) << ", "
             << std::get<1>(location) << ", " << std::get<2>(location) << "\n";
    }
    return PreservedAnalyses::all();
  };
};

} // namespace

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return {.APIVersion = LLVM_PLUGIN_API_VERSION,
          .PluginName = "Skeleton pass",
          .PluginVersion = "v0.1",
          .RegisterPassBuilderCallbacks = [](PassBuilder &PB) {
            PB.registerPipelineStartEPCallback(
                [](ModulePassManager &MPM, OptimizationLevel Level) {
                  MPM.addPass(SkeletonPass());
                });
          }};
}
