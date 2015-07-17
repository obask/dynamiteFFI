//
// Created by Oleg Baskakov on 7/17/15.
//

#ifndef DYNAMITEFFI_DECLARATIONS_H
#define DYNAMITEFFI_DECLARATIONS_H

#include <llvm-c/Core.h>

#define true LLVMRealPredicateTrue
#define false LLVMRealPredicateFalse


void initEmptyStruct(LLVMModuleRef mod, const char *name, LLVMTypeRef *PointerTy_5, LLVMTypeRef *PointerTy_6);


LLVMTypeRef initFunc0(LLVMTypeRef ResultTy);

LLVMTypeRef initFunc1(LLVMTypeRef ResultTy, LLVMTypeRef Arg1Ty);


LLVMTypeRef initFunc2(LLVMTypeRef ResultTy, LLVMTypeRef Arg1Ty, LLVMTypeRef Arg2Ty);



LLVMValueRef declareLLVMDisposeModule(LLVMModuleRef mod, LLVMTypeRef PointerTy_8);



#endif //DYNAMITEFFI_DECLARATIONS_H
