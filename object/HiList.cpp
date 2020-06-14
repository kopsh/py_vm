# include <iostream>

# include "object/HiInteger.hpp"
# include "object/HiList.hpp"
# include "object/HiString.hpp"
# include "runtime/functionObject.hpp"
# include "runtime/universe.hpp"

ListKlass* ListKlass::instance = NULL;

ListKlass* ListKlass::get_instance() {
    if (instance == NULL)
        instance = new ListKlass();

    return instance;
}

ListKlass::ListKlass() {
    HiDict* klass_dict = new HiDict();
    klass_dict->put(new HiString("append"), new FunctionObject(list_append));
    klass_dict->put(new HiString("insert"), new FunctionObject(list_insert));
    set_klass_dict(klass_dict);
}

HiList::HiList() {
    set_klass(ListKlass::get_instance());
    _inner_list = new ArrayList<HiObject*>();
}

HiList::HiList(ObjList ol) {
    set_klass(ListKlass::get_instance());
    _inner_list = ol;
}

void ListKlass::print(HiObject* x) {
    HiList* lx = (HiList* ) x;
    assert(lx && lx->klass() == (Klass* ) this);

    printf("[");

    int size = lx->size();
    if (size >= 1) {
        lx->get(0)->print();
    }
    for (int i=1; i < size; i++) {
        printf(",");
        lx->get(i)->print();
    }
    printf("]");
}

HiObject* ListKlass::subscr(HiObject* x, HiObject* y) {
    assert(x && x->klass() == ListKlass::get_instance());
    assert(y && y->klass() == IntegerKlass::get_instance());

    HiList* lx = (HiList* ) x;
    HiInteger* iy = (HiInteger* ) y;

    return lx->get(iy->value());
}

HiObject* ListKlass::contains(HiObject* x, HiObject* y) {
    assert(x && x->klass() == ListKlass::get_instance());

    HiList* lx = (HiList* ) x;

    int size = lx->size();
    for (int i=0; i < size; i++) {
        if (lx->get(i)->equal(y))
            return Universe::HiTrue;
    }
    return Universe::HiFalse;
}

HiObject* ListKlass::contains_not(HiObject* x, HiObject* y) {
    assert(x && x->klass() == ListKlass::get_instance());

    HiList* lx = (HiList* ) x;

    int size = lx->size();
    for (int i=0; i < size; i++) {
        if (lx->get(i)->equal(y))
            return Universe::HiFalse;
    }
    return Universe::HiTrue;
}

HiObject* list_append(ObjList args) {
    ((HiList*) args->get(0))->append(args->get(1));
    return (HiObject*) Universe::HiNone;
}

HiObject* list_insert(ObjList args) {
    ((HiList*) args->get(0))->insert(((HiInteger*) args->get(1))->value(), args->get(2));
    return (HiObject*) Universe::HiNone;
}