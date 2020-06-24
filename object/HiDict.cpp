# include "object/HiDict.hpp"
# include "object/HiString.hpp"
# include "runtime/functionObject.hpp"
# include "runtime/universe.hpp"
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
    klass_dict->put(new HiString("pop"), new FunctionObject(dict_pop));
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

HiObject* dict_pop(ObjList args) {
    HiDict* dict = (HiDict*) args->get(0);
    HiObject* key = args->get(1);
    HiObject* _default;
    if (args->size() == 3)
        _default = args->get(2);
    else
        _default = Universe::HiNone;

    if (dict->has_key(key))
        return dict->remove(key);
    else {
        return _default;
    }
}