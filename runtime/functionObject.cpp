# include <iostream>

# include "object/HiString.hpp"
# include "runtime/functionObject.hpp"
# include "runtime/universe.hpp"

MethodKlass* MethodKlass::instance = NULL;

MethodKlass* MethodKlass::get_instance() {
    if (instance == NULL)
        instance = new MethodKlass();

    return instance;
}

MethodKlass::MethodKlass() {
    set_klass_dict(new HiDict());
}

bool MethodObject::is_function(HiObject* x) {
    Klass* k = x->klass();
    if (k == (Klass* ) FunctionKlass::get_instance() || k == (Klass* ) NativeFunctionKlass::get_instance())
        return true;
    return false;
}

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
    _defaults = NULL;
    _closure = NULL;
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
    _globals = NULL;
    _closure = NULL;

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

HiObject* isinstance(ObjList args) {
    HiObject* x = args->get(0);
    HiObject* y = args->get(1);

    assert(y && y->klass() == TypeKlass::get_instance());

    Klass* k = x->klass();
    if (k->type_object() == y)
        return Universe::HiTrue;

    for (int i=0; i < k->mro()->size(); i++) {
        if (k->mro()->get(i) == y)
            return Universe::HiTrue;
    }

    return Universe::HiFalse;
}

HiObject* type_of(ObjList args) {
    HiObject* arg0 = args->get(0);

    return arg0->klass()->type_object();
}