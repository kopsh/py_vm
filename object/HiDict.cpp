# include "object/HiDict.hpp"
# include "object/HiString.hpp"
# include "runtime/functionObject.hpp"
# include "runtime/universe.hpp"
# include <iostream>
# include <assert.h>

/***
 * DictKlass
***/

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

void DictKlass::print(HiObject* x ) {
    HiDict* dx = (HiDict* ) x;
    assert(dx && dx->klass() == DictKlass::get_instance());

    printf("{");
    for (int i=0; i < dx->_map->size(); i++) {
        if (i > 0) {
            printf(", ");
        }
        dx->_map->entries()[i]._k->repr();
        printf(": ");
        dx->_map->entries()[i]._v->repr();
    }
    printf("}");
}

void DictKlass::repr(HiObject* x ) {
    x->print();
}


HiObject* DictKlass::subscr(HiObject* x, HiObject* y) {
    HiDict* dx = (HiDict* ) x;
    assert(dx && dx->klass() == DictKlass::get_instance());
    return dx->get(y);
}

void DictKlass::store_subscr(HiObject* x, HiObject* y, HiObject* z) {
    HiDict* dx = (HiDict* ) x;
    assert(dx && dx->klass() == DictKlass::get_instance());

    dx->put(y, z);
}

void DictKlass::delete_subscr(HiObject* x, HiObject* y) {
    HiDict* dx = (HiDict* ) x;
    assert(dx && dx->klass() == DictKlass::get_instance());

    dx->remove(x);
}

/***
 * HiDict
***/ 

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