# include <iostream>

# include "object/HiString.hpp"
# include "runtime/functionObject.hpp"

FunctionKlass* FunctionKlass::instance = NULL;

FunctionKlass* FunctionKlass::get_instance() {
    if (instance == NULL)
        instance = new FunctionKlass();

    return instance;
}

FunctionKlass::FunctionKlass() {
    
}

NativeFunctionKlass* NativeFunctionKlass::instance = NULL;

NativeFunctionKlass* NativeFunctionKlass::get_instance() {
    if (instance == NULL)
        instance = new NativeFunctionKlass();

    return instance;
}

NativeFunctionKlass::NativeFunctionKlass() {
    // set_super(FunctionKlass::get_instance());
}

FunctionObject::FunctionObject(NativeFuncPointer nfp) {
    _func_code = NULL;
    _func_name = NULL;
    _flags = 0;
    _globals = NULL;
    _native_func = nfp;

    set_klass(NativeFunctionKlass::get_instance());
}

HiObject* FunctionObject::call(ObjList args) {
    return (*_native_func)(args);
}

void FunctionKlass::print(HiObject* obj) {
    printf("<function: ");

    FunctionObject* func_obj = static_cast<FunctionObject*>(obj);

    assert(func_obj && func_obj->klass() == (Klass*) this);

    func_obj->func_name()->print();
    printf(">");
}

FunctionObject::FunctionObject(HiObject* code_obj) {
    CodeObject* co = (CodeObject* )code_obj;

    _func_code = co;
    _func_name = co->_co_name;
    _flags = co->_flag;
    _defaults = NULL;

    set_klass(FunctionKlass::get_instance());
}

void FunctionObject::set_defaults(ObjList defaults) {
    if (defaults != NULL) {
        _defaults = new ArrayList<HiObject*>(defaults);
    }
}

HiObject* len(ObjList args) {
    return args->get(0)->len();
}