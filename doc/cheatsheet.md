# Command Line Cheatsheet

##Recap:
Obtaining an executable:

    clang hello.c -o hello

Obtaining an assembly file:

    clang -S hello.c -o hello.s

Obtaining an object file:

    clang -c hello.c -o hello.o

##Obtaining LLVM IR:
Textual form:

    clang -S -emit-llvm hello.c -o hello.ll

Binary form (bitcode):

    clang -c -emit-llvm hello.c -o hello.bc

##Transforming LLVM IR:
By default, `opt` produces bitcode. Use `-S` to obtain textual IR.

    opt -pass1 [...] -passN hello.ll -o hello.bc

    opt -pass1 [...] -passN hello.ll -S -o hello.ll

##Obtaining machine code:
By default, `llc` produces assembly. Use `-filetype=obj` to obtain an object file.

    llc hello.ll -o hello.s

    llc -filetype=obj hello.ll -o hello.o

##Obtaining the results of program execution:

    lli hello.ll

##Verifying an IR module:
This is useful for checking that your pass created a well-formed module:

    opt -verify in.ll -o /dev/null

#LLVM API Cheatsheet
##Iterating through the IR:
`Module` provides `begin()` and `end()` for iterating through the functions in the module.
`Function` provides `begin()` and `end()` for iterating through the basic blocks in the function.
`BasicBlock` provides `begin()` and `end()` for iterating through the instructions in the function.

    // Range-based loops to iterate through all instructions
    for (auto &F : M)
      for (auto &BB : F)
        for (auto &I : BB)
          // Process I


Other useful iterators:
`Module::global_begin()` and `global_end()` - iterate through the globals in the module.
`Function::arg_begin()` and `arg_end()` - iterate through the function’s arguments.
##Dumping IR Objects:
Most IR objects (modules, functions, basic blocks, instructions etc) have a `dump()` method. They can usually also be printed to a stream via the `<<` operator. Streams often used for dumping objects are `dbgs()`, `errs()` and `outs()`.
##Identifying IR Objects:
Objects in the Value hierarchy use a custom, LLVM-specific RTTI system that allows us to check their types and cast between them via the `isa<>`, `cast<>` and `dyn_cast<>` templates (see [the relevant section](https://releases.llvm.org/5.0.0/docs/ProgrammersManual.html#the-isa-cast-and-dyn-cast-templates) in the [LLVM Programmer’s Manual](https://releases.llvm.org/5.0.0/docs/ProgrammersManual.html)):

    isa<ReturnInst>(&I) // Returns true or false

    auto *Casted =
      dyn_cast<CallInst>(&I) // Returns a CallInst* or nullptr

You can also check whether a `Value` is a `Constant`, a `ConstantInt`, an `Instruction`, a `BinaryOperator`, a `StoreInst`, a `TerminatorInst` etc. You should use `isa<>` when you only need a Boolean answer, and `dyn_cast<>` when you actually need more specific information about the `Value`.
##CallInst Deep Dive:
A `CallInst` contains a lot of information related to the call. We summarize the parts that could be useful for the workshop here.

Processing call arguments:

    unsigned getNumArgOperands() const;
    Value *getArgOperand(unsigned i) const; // Starts at 0

or you can iterate through the arguments via `arg_begin()` / `arg_end()` or `arg_operands()`.

Getting the called function:

    Function *getCalledFunction(); // Returns null for indirect calls

##`ConstantInt` Deep Dive:
A `ConstantInt` wraps around an `APInt` (arbitrary precision integer), which can represent a very large range of integers. For our limited use case, the most interesting method is probably

    uint64_t getLimitedValue(uint64_t Limit) const;

This will return either the integer itself if it is smaller than the limit, or the `Limit` otherwise.

##Adding new functions:
Before calling a function, you must first make sure that at least its declaration exists in the `Module`. For this, use this `Module` method:

    Constant *getOrInsertFunction(StringRef Name, FunctionType *T);

This returns a `Constant *`, but if you’re passing in the correct `FunctionType` it should always return a `Function *`, so in most cases you will just want to cast the returned value:

    auto *AddedFunc =
      cast<Function>(M.getOrInsertFunction(FunctionName, FunctionType));

##Working with Types:
You can get many simple types by using static methods from the Type class:

    static Type *getVoidTy(LLVMContext &C);

    static IntegerType *getInt32Ty(LLVMContext &C);

    static PointerType *getInt8PtrTy(LLVMContext &C, unsigned AS = 0);

Composite types such as `FunctionType` have their own static methods:

    static FunctionType *get(Type *Result,
                             ArrayRef<Type*> Params, bool isVarArg);
    // e.g. FunctionType::get(Type::getInt32Ty(Ctx),
    //                        { Type::getInt8PtrTy(Ctx),
    //                          Type::getInt32Ty(Ctx) }, false);

##Inserting LLVM IR:
The easiest way to create and insert new LLVM IR into a function is to use the `IRBuilder` class. The first thing you need to do when using it is to make sure you are inserting things in the correct place - i.e. that the insertion point of the `IRBuilder` is where you want it to be.

The IRBuilder has many constructors, but for this workshop we recommend using this one:

    explicit IRBuilder(Instruction *IP, MDNode *FPMathTag = nullptr,
                       ArrayRef<OperandBundleDef> OpBundles = None);
    // e.g. IRBuilder<> MyBuilder(MyInterestingInst);

The `IP` passed to the constructor is the insertion point - that is, the instruction in the IR before which all newly created instructions will be inserted.

If you already have an `IRBuilder` object, you can update its insertion point

    void SetInsertPoint(Instruction *I);

Methods for adding instructions:

    CallInst *CreateCall(Function *Callee, ArrayRef<Value *> Args,
                         const Twine &Name = "",
                         MDNode *FPMathTag = nullptr);
    // e.g. MyBuilder.CreateCall(MyFunc, { FirstArg, SecondArg });

Methods for adding constants:

    // 32-bit integer constant with value C
    ConstantInt *getInt32(uint32_t C);
    // N-bit integer constant with value C
    ConstantInt *getIntN(unsigned N, uint64_t C);

    // A new global variable with an initializer that has array of i8
    // type filled in with the null terminated string value specified.
    // If Name is specified, it is the name of the global variable
    // created.
    GlobalVariable *CreateGlobalString(StringRef Str,
                                       const Twine &Name = "",
                                       unsigned AddressSpace = 0);

    // Same as CreateGlobalString, but return a pointer with "i8*" type
    // instead of a pointer to array of i8.
    Value *CreateGlobalStringPtr(StringRef Str, const Twine &Name = "",
                                 unsigned AddressSpace = 0);

##Replacing uses:
Replacing all uses of a `Value` with another `Value` is a common operation in a compiler.

    void Value::replaceAllUsesWith(Value *V).

Note that `Value` may be an `Instruction`, a `Constant` etc. Also note that this does not remove the old `Value` from the IR - it just makes any place that references it to reference the new `Value` instead.
##Removing instructions:
Use `Instruction::eraseFromParent()`. Beware that this will invalidate any iterators into the parent (which means that you shouldn’t call it from a loop that iterates over the parent).