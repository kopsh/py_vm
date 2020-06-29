# include "object/HiDict.hpp"
# include "object/HiList.hpp"
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
    (new HiTypeObject())->set_own_klass(this);
    set_name(new HiString("dict"));
    set_super(ObjectKlass::get_instance());
}

void DictKlass::initialize() {
    HiDict* klass_dict = new HiDict();
    klass_dict->put(new HiString("setdefault"), new FunctionObject(set_dict_default));
    klass_dict->put(new HiString("pop"), new FunctionObject(dict_pop));

    FunctionObject* func;
    func = new FunctionObject(dict_iterkeys);
    klass_dict->put(new HiString("keys"), func);
    klass_dict->put(new HiString("iterkeys"), func);
    func = new FunctionObject(dict_itervalues);
    klass_dict->put(new HiString("values"), func);
    klass_dict->put(new HiString("itervalues"), func);
    func = new FunctionObject(dict_iteritems);
    klass_dict->put(new HiString("items"), func);
    klass_dict->put(new HiString("iteritems"), func);

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

HiObject* DictKlass::iter(HiObject* x) {
    HiDict* dx = (HiDict* ) x;
    assert(dx && dx->klass() == DictKlass::get_instance());

    HiObject* iter = new DictIterator(dx);
    iter->set_klass(DictIteratorKlass<ITER_KEY>::get_instance());
    return iter;
}

HiObject* DictKlass::allocate_instance(HiObject* callable, ArrayList<HiObject*>* args) {
    if (!args || args->length() == 0)
        return new HiDict();
    else
        return NULL;
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

/***
 * 
 * DictIterator and DictIteratorKlass
 * 
***/
DictIterator::DictIterator(HiDict* owner) {
    _owner = owner;
    _iter_cnt = 0;
}

template <ITER_TYPE n>
DictIteratorKlass<n>* DictIteratorKlass<n>::instance = NULL;

template<ITER_TYPE n>
DictIteratorKlass<n>* DictIteratorKlass<n>::get_instance() {
    if (instance == NULL) {
        instance = new DictIteratorKlass<n>();
    }

    return instance;
}

template <ITER_TYPE iter_type>
DictIteratorKlass<iter_type>::DictIteratorKlass() {
    const char* names[] = {
        "dict_keyiterator",
        "dict_valueiterator",
        "dict_itemiterator"
    };
    HiDict* klass_dict = new HiDict();
    set_klass_dict(klass_dict);
    set_name(new HiString(names[iter_type]));
}

template <ITER_TYPE iter_type>
HiObject* DictIteratorKlass<iter_type>::next(HiObject* x) {
    DictIterator* i = (DictIterator* ) x;

    int iter_cnt = i->iter_cnt();
    HiObject* obj;
    if (iter_cnt < i->owner()->size()) {
        switch (iter_type)
        {
            case ITER_KEY:
                obj = i->owner()->map()->get_key(iter_cnt);
                break;
                
            case ITER_VALUE:
                obj = i->owner()->map()->get_value(iter_cnt);
                break;

            case ITER_ITEM:
                HiList* lobj = new HiList();
                lobj->append(i->owner()->map()->get_key(iter_cnt));
                lobj->append(i->owner()->map()->get_value(iter_cnt));
                obj = lobj;
                break;
        }
        i->inc_cnt();
        return obj;
    }
    else
        return NULL;
}

HiObject* dict_iterkeys(ObjList args) {
    HiDict* d = (HiDict*) args->get(0);
    HiObject* iter = new DictIterator(d);
    iter->set_klass(DictIteratorKlass<ITER_KEY>::get_instance());
    return iter;
}

HiObject* dict_itervalues(ObjList args) {
    HiDict* d = (HiDict*) args->get(0);
    HiObject* iter = new DictIterator(d);
    iter->set_klass(DictIteratorKlass<ITER_VALUE>::get_instance());
    return iter;
}

HiObject* dict_iteritems(ObjList args) {
    HiDict* d = (HiDict*) args->get(0);
    HiObject* iter = new DictIterator(d);
    iter->set_klass(DictIteratorKlass<ITER_ITEM>::get_instance());
    return iter;
}