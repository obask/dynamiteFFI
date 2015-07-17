#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Transforms/Scalar.h>
#include <stdio.h>
#include "declarations.h"


// clang-mp-3.6 -S -c -emit-llvm -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS debug.c
// llc-mp-3.6 -march=cpp debug.ll -o main2.cpp

// надо перевести большинство функций в байткод, т.к. нет парсера *.h файлов
// а llc -march=cpp не умеет генерить сишный код
// в будущем это должен делать FFI, в том числе разворачивать инфиксную нотацию для вызова методов

// Лучше забить на контекст, получается многобуков
//     LLVMModuleRef module = LLVMModuleCreateWithNameInContext("debug.ll", context);

// За счет того что тут посути Multi Stage Programming,
// типы одновременно являются переменными и называются с большой буквы.
// В основном, ради соответствию оригиналу


void DEBUG()
{
    printf("START\n");

    LLVMContextRef ctx = LLVMGetGlobalContext();
    LLVMModuleRef mod = LLVMModuleCreateWithName("debug.ll");
//    LLVMSetDataLayout(mod, "0x7fe0cb4083a0");
    LLVMSetTarget(mod, "x86_64-apple-macosx10.10.0");

    // создавать узел под каждый const char[9] это ад
    LLVMTypeRef Int8Type = LLVMInt8Type();
    LLVMTypeRef ArrayTy_0 = LLVMArrayType(Int8Type, 9);
    // а это уже чит с типами, видимо наследие старого API
    LLVMTypeRef PointerTy_1 = LLVMPointerType(ArrayTy_0, 0);
    LLVMTypeRef ArrayTy_2 = LLVMArrayType(Int8Type, 27);
    LLVMTypeRef PointerTy_3 = LLVMPointerType(ArrayTy_2, 0);


    LLVMTypeRef PointerTy_5;
    LLVMTypeRef PointerTy_6;
    initEmptyStruct(mod, "struct.LLVMOpaqueContext", &PointerTy_5, &PointerTy_6);
    LLVMTypeRef PointerTy_7;
    LLVMTypeRef PointerTy_8;
    initEmptyStruct(mod, "struct.LLVMOpaqueModule", &PointerTy_7, &PointerTy_8);

    LLVMTypeRef FuncTy_10;
    FuncTy_10 = initFunc0(/*res type*/PointerTy_6);

    LLVMTypeRef PointerTy_9 = LLVMPointerType(FuncTy_10, 0);
    LLVMTypeRef PointerTy_11 = LLVMPointerType(Int8Type, 0);

    LLVMTypeRef FuncTy_13;
    FuncTy_13 = initFunc2(PointerTy_8,/*arg types=*/ PointerTy_11, PointerTy_6);
    LLVMTypeRef PointerTy_12 = LLVMPointerType(FuncTy_13, 0);

    LLVMTypeRef FuncTy_15;
    FuncTy_15 = initFunc2(LLVMVoidType(),/*arg types=*/ PointerTy_8, PointerTy_11);
    LLVMTypeRef PointerTy_14 = LLVMPointerType(FuncTy_13, 0);




    declareLLVMDisposeModule(mod, PointerTy_8);


    // don't forget destructors
    LLVMDisposeModule(mod);
    printf("FINISH\n");

}




int
main() {

    DEBUG();


    return 0;
}

