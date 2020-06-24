# include "object/HiDict.hpp"
# include "object/HiString.hpp"
# include "runtime/functionObject.hpp"
# include <iostream>

DictKlass* DictKlass::instance = NULL;

DictKlass* DictKlass::get_instance() {
    if (instance == NULL)
        instance = new DictKlass();
    return instance;
}

DictKlass::DictKlass() {

}

void DictKlass::initialize() {
    HiDict* klass_dict = new HiDict();
    klass_dict->put(new HiString("setdefault"), new FunctionObject(set_dict_default));
    set_klass_dict(klass_dict);
}

HiDict::HiDict() {
    _map = new Map<HiObject*, HiObject*>();
    set_klass(DictKlass::get_instance());
}

HiDict::HiDict(ObjMap map) {
    _map = map;
    set_klass(DictKlass::get_instance());
}

HiObject* set_dict_default(ObjList args) {
    HiDict* dict = (HiDict*) args->get(0);
    HiObject* key = args->get(1);
    HiObject* value = args->get(2);

    if (!dict->has_key(key)) {
        dict->put(key, value);
    }
    else {
        return dict->get(key);
    }

    return value;
}