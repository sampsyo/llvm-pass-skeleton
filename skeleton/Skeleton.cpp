#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
using namespace llvm;

namespace {

struct SkeletonPass : public PassInfoMixin<SkeletonPass> {
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
        for (auto &F : M.functions()) {

            // Get the function to call from our runtime library.
            LLVMContext &Ctx = F.getContext();
            std::vector<Type*> paramTypes = {Type::getInt32Ty(Ctx)};
            Type *retType = Type::getVoidTy(Ctx);
            FunctionType *logFuncType = FunctionType::get(retType, paramTypes, false);
            FunctionCallee logFunc =
                F.getParent()->getOrInsertFunction("logop", logFuncType);

            for (auto &B : F) {
                for (auto &I : B) {
                    if (auto *op = dyn_cast<BinaryOperator>(&I)) {
                        // Insert *after* `op`.
                        IRBuilder<> builder(op);
                        builder.SetInsertPoint(&B, ++builder.GetInsertPoint());

                        // Insert a call to our function.
                        Value* args[] = {op};
                        builder.CreateCall(logFunc, args);

                        return PreservedAnalyses::none();
                    }
                }
            }

        }
        return PreservedAnalyses::all();
    }
};

}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
    return {
        .APIVersion = LLVM_PLUGIN_API_VERSION,
        .PluginName = "Skeleton pass",
        .PluginVersion = "v0.1",
        .RegisterPassBuilderCallbacks = [](PassBuilder &PB) {
            PB.registerPipelineStartEPCallback(
                [](ModulePassManager &MPM, OptimizationLevel Level) {
                    MPM.addPass(SkeletonPass());
                });
        }
    };
}
