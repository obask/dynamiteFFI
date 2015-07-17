# dynamiteFFI
FFI to call pure-c functions


### Почему нужен отдельный проект под FFI?

Все просто -- пока Dynamite написан на c++, а FFI для получения чистого байткода надо делать на pure C.

Изначально, планировалось генерировать вызовы c++ когда сразу в байткоде.
Каждая функция, не имеющая extern_C, при этом прореживается названием namespace, количеством букв в названии и своим типом.

    %19 = call %"class.llvm::StructType"* @_ZNK4llvm6Module13getTypeByNameENS_9StringRefE(%"class.llvm::Module"* %7, i8* %16, i64 %18)

Гораздо проще спрятать весь байткод, полученный из c++ в отдельный объектный файл *.bc, воспользовавшись подходом LLVM.

Для этого понадобятся:

1. Магический макрос, оборачивающий указатели в пустые типы языка C

    #define DEFINE_SIMPLE_CONVERSION_FUNCTIONS(ty, ref)     \
      inline ty *unwrap(ref P) {                            \
        return reinterpret_cast<ty*>(P);                    \
      }                                                     \
                                                            \
      inline ref wrap(const ty *P) {                        \
        return reinterpret_cast<ref>(const_cast<ty*>(P));   \
      }
    
    // Create wrappers for C Binding types (see CBindingWrapping.h).
    DEFINE_SIMPLE_CONVERSION_FUNCTIONS(CPP_TYPE_NAME, PURE_C_TYPE_NAME)

2. Типобезопасная заглушка, стирающая информацию об указателе

    /**
     * The top-level container for all other LLVM Intermediate Representation (IR)
     * objects.
     *
     * @see llvm::Module
     */
    typedef struct LLVMOpaqueModule *LLVMModuleRef;

    // это указатель на пустую структуру %"class.llvm::StringRef" = type { }


3. Обертка над вызовом функции, позволяющая скрыть implicit приведение типов

    void LLVMSetTarget(LLVMModuleRef M, const char *Triple) {
        unwrap(M)->setTargetTriple(Triple);
    }

4. Заголовочный файл Core.h, содержащий объявление типов и сигнатур методов

    void LLVMSetTarget(LLVMModuleRef M, const char *Triple);


#### Например, так захламляет код компилятор Cpp:

Это был вызов вида

    mod->getTypeByName(make_string_ref("struct.NewCppClass"));

Который транслируется(по аналогии с языком Go) в вызов, первым аргументом которого добавляется ссылка но объект this

    %19 = call %"class.llvm::StructType"* @_ZNK4llvm6Module13getTypeByNameENS_9StringRefE(%"class.llvm::Module"* %7, i8* %16, i64 %18)



Но, благодаря implicit conversion типа const char * в StringRef создается вот такая милая функция

    %"class.llvm::StringRef" = type { i8*, i64 }
    %"class.llvm::Module" = type { %"class.llvm::LLVMContext"*, %"class.llvm::iplist", %"class.llvm::iplist.0", %"class.llvm::iplist.9", %"struct.llvm::ilist", %"class.std::__1::basic_string", %"class.llvm::ValueSymbolTable"*, %"class.llvm::StringMap", %"class.std::__1::unique_ptr", %"class.std::__1::basic_string", %"class.std::__1::basic_string", i8*, %"class.std::__1::basic_string", %"class.llvm::DataLayout" }
    %"class.llvm::iplist" = type { %"struct.llvm::ilist_traits", %"class.llvm::GlobalVariable"* }
    ...
    100 more LOC
    ...
    %"class.llvm::StructType" = type { %"class.llvm::CompositeType", i8* }
    %"class.llvm::CompositeType" = type { %"class.llvm::Type" }
    %"class.std::__1::__basic_string_common" = type { i8 }

    ; Function Attrs: ssp uwtable
    define linkonce_odr void @_ZN4llvm6Module15setTargetTripleENS_9StringRefE(%"class.llvm::Module"* %this, i8* %T.coerce0, i64 %T.coerce1) #0 align 2 {
      %1 = alloca %"class.std::__1::__libcpp_compressed_pair_imp"*, align 8
      %2 = alloca %"class.std::__1::__compressed_pair"*, align 8
    ...
    300 more LOC
    ...
      store i32 %178, i32* %__i.i.i.i, align 4
      br label %169
    
    _ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEaSEOS5_.exit: ; preds = %169
      call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %52) #6
      ret void
    }


