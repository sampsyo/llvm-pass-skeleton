#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include  <iostream>

using namespace llvm;

namespace {

/*
 * https://github.com/alexjung/Writing-an-LLVM-Pass-using-the-new-PassManager
 * and
 * https://llvm.org/docs/WritingAnLLVMNewPMPass.html
 * are indispensable for getting a basic understanding of the pass architecture of llvm.
 */
struct SkeletonPass : public PassInfoMixin<SkeletonPass> {

    PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM) {
        std::cout << "SkeletonPass in function: " << F.getName().str() << std::endl;
        return PreservedAnalyses::all();
    };

    static bool isRequired() {
        return true;
    }
};

}

void registerHelloWorldPassBuilderCallback(PassBuilder &PB) {
    PB.registerPipelineParsingCallback(
        [](StringRef Name, FunctionPassManager &FPM, ArrayRef<PassBuilder::PipelineElement>) {
            if (Name == "skeleton") {
                FPM.addPass(SkeletonPass());
                return true;
            }
            return false;
        }
    );
}

PassPluginLibraryInfo getHelloWorldPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "Skeleton", LLVM_VERSION_STRING, registerHelloWorldPassBuilderCallback};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getHelloWorldPluginInfo();
}