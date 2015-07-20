#include <llvm-c/Analysis.h>
#include <llvm-c/Core.h>
#include <stdio.h>
//#include "declarations.h"


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


//void DEBUG()
//{
//    printf("START\n");
//
//    LLVMContextRef ctx = LLVMGetGlobalContext();
//    LLVMModuleRef mod = LLVMModuleCreateWithName("debug.ll");
////    LLVMSetDataLayout(mod, "0x7fe0cb4083a0");
//    LLVMSetTarget(mod, "x86_64-apple-macosx10.10.0");
//
//    // создавать узел под каждый const char[9] это ад
//    LLVMTypeRef Int8Type = LLVMInt8Type();
//    LLVMTypeRef ArrayTy_0 = LLVMArrayType(Int8Type, 9);
//    // а это уже чит с типами, видимо наследие старого API
//    LLVMTypeRef PointerTy_1 = LLVMPointerType(ArrayTy_0, 0);
//    LLVMTypeRef ArrayTy_2 = LLVMArrayType(Int8Type, 27);
//    LLVMTypeRef PointerTy_3 = LLVMPointerType(ArrayTy_2, 0);
//
//
//    LLVMTypeRef PointerTy_5;
//    LLVMTypeRef PointerTy_6;
//    initEmptyStruct(mod, "struct.LLVMOpaqueContext", &PointerTy_5, &PointerTy_6);
//    LLVMTypeRef PointerTy_7;
//    LLVMTypeRef PointerTy_8;
//    initEmptyStruct(mod, "struct.LLVMOpaqueModule", &PointerTy_7, &PointerTy_8);
//
//    LLVMTypeRef FuncTy_10;
//    FuncTy_10 = initFunc0(/*res type*/PointerTy_6);
//
//    LLVMTypeRef PointerTy_9 = LLVMPointerType(FuncTy_10, 0);
//    LLVMTypeRef PointerTy_11 = LLVMPointerType(Int8Type, 0);
//
//    LLVMTypeRef FuncTy_13;
//    FuncTy_13 = initFunc2(PointerTy_8,/*arg types=*/ PointerTy_11, PointerTy_6);
//    LLVMTypeRef PointerTy_12 = LLVMPointerType(FuncTy_13, 0);
//
//    LLVMTypeRef FuncTy_15;
//    FuncTy_15 = initFunc2(LLVMVoidType(),/*arg types=*/ PointerTy_8, PointerTy_11);
//    LLVMTypeRef PointerTy_14 = LLVMPointerType(FuncTy_13, 0);
//
//
//
//
//    declareLLVMDisposeModule(mod, PointerTy_8);
//
//
//    // don't forget destructors
//    LLVMDisposeModule(mod);
//    printf("FINISH\n");
//
//}


//typedef struct ObjectX* ObjectXRef;
//
//
//
//void ZZZZZ(ObjectXRef AAAAA) {
//    LLVMModuleCreateWithName((const char*)AAAAA);
//}


#define true LLVMRealPredicateTrue
#define false LLVMRealPredicateFalse


LLVMModuleRef DEBUG() {
    unsigned LLVMCCallConv = 0;

    // Module Construction
    LLVMContextRef ctx = LLVMGetGlobalContext();
    LLVMModuleRef mod = LLVMModuleCreateWithName("debug.ll");
    LLVMSetTarget(mod, "x86_64-apple-macosx10.10.0");

    // Type Definitions
    LLVMTypeRef Int8Type = LLVMInt8Type();
    LLVMTypeRef Int32Type = LLVMInt32Type();
    LLVMTypeRef ArrayTy_0 = LLVMArrayType(Int8Type, 7);

    LLVMTypeRef PointerTy_1 = LLVMPointerType(ArrayTy_0, 0);

    unsigned args_count13 = 0;
    LLVMTypeRef FuncTy_2_args[args_count13];

    LLVMTypeRef FuncTy_2 = LLVMFunctionType(
            /*Result=*/Int32Type,
            /*Params=*/FuncTy_2_args,
                       args_count13,
            /*isVarArg=*/false);


    LLVMTypeRef PointerTy_3 = LLVMPointerType(Int32Type, 0);
    LLVMTypeRef PointerTy_4 = LLVMPointerType(Int8Type, 0);


    unsigned args_count6 = 1;
    LLVMTypeRef FuncTy_6_args[args_count6];
    FuncTy_6_args[0] = PointerTy_4;

    LLVMTypeRef FuncTy_6 = LLVMFunctionType(
            /*Result=*/Int32Type,
            /*Params=*/FuncTy_6_args,
                       args_count6,
            /*isVarArg=*/true);

    LLVMTypeRef PointerTy_5 = LLVMPointerType(FuncTy_6, 0);

    // Function Declarations
    LLVMValueRef func_main = LLVMGetNamedFunction(mod, "main");
    if (!func_main) {
        func_main = LLVMAddFunction(
                mod,
                /*Name=*/"main",
                /*Type=*/FuncTy_2
        );
        // (external, no body)
        LLVMSetFunctionCallConv(func_main, LLVMCCallConv);
    }

    LLVMValueRef func_printf = LLVMGetNamedFunction(mod, "printf");
    if (!func_printf) {
        func_printf = LLVMAddFunction(
                mod,
                /*Name=*/"printf",
                /*Type=*/FuncTy_6
        );
        // (external, no body)
        LLVMSetFunctionCallConv(func_printf, LLVMCCallConv);
    }

    // Global Variable Declarations

    LLVMValueRef gvar_array__str = LLVMAddGlobal(mod, ArrayTy_0, ".str");
    LLVMSetAlignment(gvar_array__str, 1);

    // Constant Definitions
    LLVMValueRef const_array_7 = LLVMConstString("Hello\n", 7, true);

    LLVMValueRef ZERO = LLVMConstInt(Int32Type, /*N=*/ 0, /*ext=*/ 0);

    LLVMValueRef const_ptr_10_indices[2];
    const_ptr_10_indices[0] = ZERO;
    const_ptr_10_indices[1] = ZERO;

    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMValueRef const_ptr_10 = LLVMBuildInBoundsGEP(builder, gvar_array__str, const_ptr_10_indices, 2, "NAME");

    // Global Variable Definitions
    LLVMSetInitializer(gvar_array__str, const_array_7);

    // Function Definitions

    // Function: main (func_main)

    LLVMBasicBlockRef basicBlock = LLVMAppendBasicBlock(func_main, "entry");

    LLVMPositionBuilderAtEnd(builder, basicBlock);


    // Block  (label_11)
    LLVMValueRef ptr_12 = LLVMBuildAlloca(builder, Int32Type, "ptr_12");
    LLVMValueRef void_13 = LLVMBuildStore(builder, ZERO, ptr_12);
    LLVMValueRef ttt[1];
    ttt[0] = const_ptr_10;
    LLVMValueRef int32_14 = LLVMBuildCall(builder, func_printf, ttt, 1, "int32_14");


//    LLVMSetFunctionCallConv(int32_14, LLVMCCallConv);

    LLVMSetTailCall(int32_14, false);

    LLVMBuildRet(builder, ZERO);


    return mod;
}


int
main() {

    LLVMModuleRef module = DEBUG();
    char *msg;
    LLVMVerifyModule(module, LLVMPrintMessageAction, &msg);
    LLVMPassManagerRef passManager = LLVMCreatePassManager();
    LLVMRunPassManager(passManager, module);
    LLVMDisposeMessage(msg);

    LLVMDumpModule(module);

//    LLVMDisposeModule(module);

    return 0;
}

