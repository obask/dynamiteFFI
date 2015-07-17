//
// Created by Oleg Baskakov on 7/17/15.
//

#include "declarations.h"



void initEmptyStruct(LLVMModuleRef mod, const char *name, LLVMTypeRef *PointerTy_5, LLVMTypeRef *PointerTy_6)
{
    LLVMContextRef ctx = LLVMGetGlobalContext();
    LLVMTypeRef StructTy_struct_LLVMOpaqueContext = LLVMGetTypeByName(mod, name);
    // проверку можно выпилить т.к. это definition, который бывает только из header файлов
    if (!StructTy_struct_LLVMOpaqueContext) {
        StructTy_struct_LLVMOpaqueContext = LLVMStructCreateNamed(ctx, name);
    }
    unsigned fields_count = 0;
    LLVMTypeRef StructTy_struct_LLVMOpaqueContext_fields[fields_count];
    if (LLVMIsOpaqueStruct(StructTy_struct_LLVMOpaqueContext)) {
        LLVMStructSetBody(StructTy_struct_LLVMOpaqueContext,
                          StructTy_struct_LLVMOpaqueContext_fields,
                /*ElementCount=*/fields_count, /*isPacked=*/0);
    }

    // return
    *PointerTy_6 = LLVMPointerType(StructTy_struct_LLVMOpaqueContext, 0);
    *PointerTy_5 = LLVMPointerType(*PointerTy_6, 0);
}

LLVMTypeRef initFunc0(LLVMTypeRef ResultTy)
{
    LLVMTypeRef Int8Type = LLVMInt8Type();
    unsigned args_count = 0;
    LLVMTypeRef FuncTy_10_args[args_count];
    return LLVMFunctionType(
            /*Result=*/ResultTy,
            /*Params=*/FuncTy_10_args,
                       args_count,
            /*isVarArg=*/false);
}

LLVMTypeRef initFunc1(LLVMTypeRef ResultTy, LLVMTypeRef Arg1Ty)
{
    unsigned args_count13 = 2;
    LLVMTypeRef FuncTy_13_args[args_count13];
    {
        int i = 0;
        FuncTy_13_args[i++] = Arg1Ty;
    }
    return LLVMFunctionType(
            /*Result=*/ResultTy,
            /*Params=*/FuncTy_13_args,
                       args_count13,
            /*isVarArg=*/false);
}

LLVMTypeRef initFunc2(LLVMTypeRef ResultTy, LLVMTypeRef Arg1Ty, LLVMTypeRef Arg2Ty)
{
    unsigned args_count13 = 2;
    LLVMTypeRef FuncTy_13_args[args_count13];
    {
        int i = 0;
        FuncTy_13_args[i++] = Arg1Ty;
        FuncTy_13_args[i++] = Arg2Ty;
    }
    return LLVMFunctionType(
            /*Result=*/ResultTy,
            /*Params=*/FuncTy_13_args,
                       args_count13,
            /*isVarArg=*/false);
}



LLVMValueRef declareLLVMDisposeModule(LLVMModuleRef mod, LLVMTypeRef PointerTy_8)
{
    LLVMTypeRef FuncTy_17 = initFunc1(LLVMVoidType(), PointerTy_8);

    LLVMValueRef func_LLVMDisposeModule = LLVMGetNamedFunction(mod, "LLVMDisposeModule");

    if (!func_LLVMDisposeModule) {
        func_LLVMDisposeModule = LLVMAddFunction(
                mod,
                /*Name=*/"LLVMDisposeModule",
                /*Type=*/FuncTy_17
        );
        // (external, no body)
        LLVMSetFunctionCallConv(func_LLVMDisposeModule, LLVMCCallConv);
    }
// FIXME    LLVMAddFunctionAttr(func_LLVMDisposeModule, )
    return func_LLVMDisposeModule;
}
