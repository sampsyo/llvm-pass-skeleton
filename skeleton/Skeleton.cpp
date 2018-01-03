#include "llvm/Pass.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#define DEBUG_TYPE "skeleton"

using namespace llvm;

namespace {
struct SkeletonPass : public FunctionPass {
  static char ID;
  SkeletonPass() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    DEBUG(dbgs() << "I saw a function called " << F.getName() << "!\n");

    // TODO 1: Dump all instructions in F
    // TODO 2: Dump only the calls in F
    // TODO 3: Dump only calls to the "fib" function with constant parameters
    // TODO 4: Replace constant calls to fib with the result

    // We should return true if we have modified the IR and false otherwise.
    return true;
  }

private:
  // Check that the function is the 'fib' that we expect - i.e. that it has the
  // correct name and signature (takes an i32, returns an i32).
  bool isFibFunction(Function *F) const {
    auto *FTy = F->getFunctionType();

    return F->getName() == "fib" && FTy->getNumParams() == 1 &&
      FTy->getReturnType()->isIntegerTy(32) &&
      FTy->getParamType(0)->isIntegerTy(32);
  }

  // Returns the value of the \p n'th Fibonacci number.
  int fib(int n) {
    // Precomputed Fibonacci numbers F0 up to F46. This implementation assumes that
    // the size n of the input array fits in 4 bytes. Note that F46=1836311903 is
    // the largest Fibonacci number that is less or equal to the 4-byte
    // INT_MAX (=2147483647). The next Fibonacci number, i.e. F47, is 2971215073
    // and is larger than INT_MAX, implying that it does not fit in a 4 byte
    // integer.
    const static int Fib[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233,
      377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025,
      121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887,
      9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141,
      267914296, 433494437, 701408733, 1134903170, 1836311903};
    const int max = sizeof(Fib) / sizeof(*Fib);

    if (n <= 0)
      return 0;

    if (n >= max)
      return INT_MAX;

    return Fib[n];
  }
};
}

char SkeletonPass::ID = 0;

// Make the pass visible to opt.
static RegisterPass<SkeletonPass> X("skeleton", "Skeleton Pass");

// Automatically enable the pass in clang.
// http://adriansampson.net/blog/clangpass.html
static void registerSkeletonPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new SkeletonPass());
}

static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerSkeletonPass);
