# include <iostream>

# include "object/HiInteger.hpp"
# include "object/HiList.hpp"

ListKlass* ListKlass::instance = NULL;

ListKlass* ListKlass::get_instance() {
    if (instance == NULL)
        instance = new ListKlass();

    return instance;
}

ListKlass::ListKlass() {

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
