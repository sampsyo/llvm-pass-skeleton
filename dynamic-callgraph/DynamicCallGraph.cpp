#include "llvm/Pass.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#define DEBUG_TYPE "dynamic-call-graph"

using namespace llvm;

namespace {
struct DynamicCallGraphPass : public ModulePass {
  static char ID;
  DynamicCallGraphPass() : ModulePass(ID) {}

  bool runOnModule(Module &M) override {
    LLVMContext &Context = M.getContext();

    for (Function &F : M) {
      // Print prologue and epilogue from 'main' function
      if (F.getName() == "main") {

        FunctionType *PPET =
          FunctionType::get(Type::getVoidTy(Context), {}, false);
        Constant *PProF = M.getOrInsertFunction("print_prologue", PPET);
        Constant *PEpiF = M.getOrInsertFunction("print_epilogue", PPET);

        // Call 'print_prologue' on entry
        Instruction &EI = *(F.begin()->begin());
        IRBuilder<> ProBuilder(&EI);
        ProBuilder.CreateCall(cast<Function>(PProF), {});

        // TODO 1: Call 'print_epilogue' before each return from main, so we can
        //         obtain a well-formed dot file.
      }

      // TODO 2: Add the declaration for the 'print_edge' function to the module.
      // TODO 3: Call 'print_edge' before each call instruction
    }

    return true;
  }

};
}

char DynamicCallGraphPass::ID = 0;

// Make the pass visible to opt.
static RegisterPass<DynamicCallGraphPass>
X("dynamic-call-graph", "Dynamic Call Graph Pass");

// Automatically enable the pass in clang.
// http://adriansampson.net/blog/clangpass.html
static void registerDynamicCallGraphPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new DynamicCallGraphPass());
}

static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerDynamicCallGraphPass);
