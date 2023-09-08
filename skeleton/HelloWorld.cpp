#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include  <iostream>


using namespace llvm;
namespace {
struct HelloWorldPass : public PassInfoMixin<HelloWorldPass> {

    PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM) {
        std::cout << "HelloWorldPass in function: " << F.getName().str() << std::endl;
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
            if (Name == "hello-world") {
                FPM.addPass(HelloWorldPass());
                return true;
            }
            return false;
        }
    );
}

PassPluginLibraryInfo getHelloWorldPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "HelloWorld", LLVM_VERSION_STRING, registerHelloWorldPassBuilderCallback};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getHelloWorldPluginInfo();
}