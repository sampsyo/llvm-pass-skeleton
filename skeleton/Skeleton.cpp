#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
using namespace llvm;

namespace {
  struct SkeletonPass : public FunctionPass {
    static char ID;
    SkeletonPass() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      errs() << "In a function called " << F.getName() << "!\n";

      errs() << "Function body:\n";
      //F.dump(); Out-of-Date: no more dump support in modern llvm unless you enable it at compile time.
      F.print(llvm::errs());

      for (auto &B : F) {
        errs() << "Basic block:\n";
        B.print(llvm::errs());

        for (auto &I : B) {
          errs() << "Instruction: \n";
          I.print(llvm::errs(), true);
          errs() << "\n";
        }
      }

      return false;
    }
  };
}

/* Register Legacy Pass */
char SkeletonPass::ID = 0;

/* Make the pass callable using `-skeleton`, as suggested by LLVM docs */
static RegisterPass<SkeletonPass> 
RegisterMyPass("skeleton", "Skeleton Pass",
      false, // This pass doesn't modify the CFG => true
      false // This pass is not a pure analysis pass => false
      );

static llvm::RegisterStandardPasses Y(
    llvm::PassManagerBuilder::EP_EarlyAsPossible,
    [](const llvm::PassManagerBuilder &Builder,
       llvm::legacy::PassManagerBase &PM) { PM.add(new SkeletonPass()); });

