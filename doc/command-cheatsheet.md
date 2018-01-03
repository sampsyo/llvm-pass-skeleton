# Command Line Cheatsheet

## Recap:
Obtaining an executable:

    clang hello.c -o hello

Obtaining an assembly file:

    clang -S hello.c -o hello.s

Obtaining an object file:

    clang -c hello.c -o hello.o

## Obtaining LLVM IR:
Textual form:

    clang -S -emit-llvm hello.c -o hello.ll

Binary form (bitcode):

    clang -c -emit-llvm hello.c -o hello.bc

## Transforming LLVM IR:
By default, `opt` produces bitcode. Use `-S` to obtain textual IR.

    opt -pass1 [...] -passN hello.ll -o hello.bc

    opt -pass1 [...] -passN hello.ll -S -o hello.ll

## Obtaining machine code:
By default, `llc` produces assembly. Use `-filetype=obj` to obtain an object file.

    llc hello.ll -o hello.s

    llc -filetype=obj hello.ll -o hello.o

## Obtaining the results of program execution:

    lli hello.ll

## Verifying an IR module:
This is useful for checking that your pass created a well-formed module:

    opt -verify in.ll -o /dev/null
