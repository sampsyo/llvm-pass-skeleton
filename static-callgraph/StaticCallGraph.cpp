#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Debug.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

extern "C" {
#include "callgraph/cg.h"
}

#define DEBUG_TYPE "static-call-graph"

using namespace llvm;

namespace {
struct StaticCallGraphPass : public ModulePass {
  static char ID;
  StaticCallGraphPass() : ModulePass(ID) {}

  bool runOnModule(Module &M) override {
    print_prologue();

    // TODO: For each call instruction, use print_edge with the name of the
    // current function and the name of the called function.

    print_epilogue();
    return false;
  }
};
}

char StaticCallGraphPass::ID = 0;

// Make the pass visible to opt.
static RegisterPass<StaticCallGraphPass>
X("static-call-graph", "Static Call Graph Pass");

// Automatically enable the pass in clang.
// http://adriansampson.net/blog/clangpass.html
static void registerStaticCallGraphPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new StaticCallGraphPass());
}

static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EnabledOnOptLevel0,
                 registerStaticCallGraphPass);
