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

    set_klass(FunctionKlass::get_instance());
}