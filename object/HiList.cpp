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
    klass_dict->put(new HiString("index"), new FunctionObject(list_index));
    klass_dict->put(new HiString("pop"), new FunctionObject(list_pop));
    klass_dict->put(new HiString("remove"), new FunctionObject(list_remove));
    klass_dict->put(new HiString("reverse"), new FunctionObject(list_reverse));
    klass_dict->put(new HiString("sort"), new FunctionObject(list_sort));
    set_klass_dict(klass_dict);

    (new HiTypeObject())->set_own_klass(this);
    set_name(new HiString("list"));
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
        lx->get(0)->repr();
    }
    for (int i=1; i < size; i++) {
        printf(",");
        lx->get(i)->repr();
    }
    printf("]");
}

void ListKlass::repr(HiObject* x) {
    x->print();
}

HiObject* ListKlass::subscr(HiObject* x, HiObject* y) {
    assert(x && x->klass() == ListKlass::get_instance());
    assert(y && y->klass() == IntegerKlass::get_instance());

    HiList* lx = (HiList* ) x;
    HiInteger* iy = (HiInteger* ) y;

    return lx->get(iy->value());
}

void ListKlass::store_subscr(HiObject* x, HiObject* y, HiObject* z) {
    assert(x && x->klass() == ListKlass::get_instance());
    assert(y && y->klass() == IntegerKlass::get_instance());

    HiList* lx = (HiList* ) x;
    HiInteger* iy = (HiInteger* ) y;

    lx->set(iy->value(), z);
}

void ListKlass::delete_subscr(HiObject* x, HiObject* y) {
    assert(x && x->klass() == ListKlass::get_instance());
    assert(y && y->klass() == IntegerKlass::get_instance());

    HiList* lx = (HiList* ) x;
    HiInteger* iy = (HiInteger* ) y;

    lx->delete_index(iy->value());
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

HiObject* ListKlass::iter(HiObject* x) {
    assert(x && x->klass() == ListKlass::get_instance());

    HiList* lx = (HiList* ) x;
    return new ListIterator(lx);
}

HiObject* ListKlass::add(HiObject* x, HiObject* y) {
    HiList* lx = (HiList*)x;
    assert(lx && lx->klass() == (Klass*) this);
    HiList* ly = (HiList*)y;
    assert(ly && ly->klass() == (Klass*) this);

    HiList* z = new HiList();
    for (int i = 0; i < lx->size(); i++) {
        z->inner_list()->set(i, lx->inner_list()->get(i));
    }

    for (int i = 0; i < ly->size(); i++) {
        z->inner_list()->set(i + lx->size(),
                ly->inner_list()->get(i));
    }

    return z;
}

/*
    list klass_dict functions
*/

HiObject* list_append(ObjList args) {
    ((HiList*) args->get(0))->append(args->get(1));
    return (HiObject*) Universe::HiNone;
}

HiObject* list_insert(ObjList args) {
    ((HiList*) args->get(0))->insert(((HiInteger*) args->get(1))->value(), args->get(2));
    return (HiObject*) Universe::HiNone;
}

HiObject* list_index(ObjList args) {
    HiList* list = (HiList*) (args->get(0));
    HiObject* target = args->get(1);

    for (int i=0; i < list->size(); i++) {
        if (list->get(i)->equal(target) == Universe::HiTrue) {
            return new HiInteger(i);
        }
    }
    return Universe::HiNone;
}

HiObject* list_pop(ObjList args) {
    HiList* list = (HiList*) (args->get(0));
    return list->pop();
}

HiObject* list_remove(ObjList args) {
    HiList* list = (HiList*) (args->get(0));
    HiObject* target = args->get(1);

    for (int i=0; i < list->size(); i++) {
        if (list->get(i)->equal(target) == Universe::HiTrue) {
            list->delete_index(i);
            break;
        }
    }
    return Universe::HiNone;
}

HiObject* list_reverse(ObjList args) {
    HiList* list = (HiList*) (args->get(0));
    HiObject *a, *b;

    int l = 0;
    int r = list->size()-1;
    while (l < r) {
        a = list->inner_list()->get(l);
        b = list->inner_list()->get(r);
        list->set(l, b);
        list->set(r, a);
        l++;
        r--;
    }
    return Universe::HiNone;
}

HiObject* list_sort(ObjList args) {
    HiList* list = (HiList*) (args->get(0));
    quicksort(list->inner_list(), 0, list->size()-1);
    return Universe::HiNone;
}

/* 
    list sort functions
*/
void quicksort(ArrayList<HiObject*>* list, int left, int right) {
    if (left >= right)
        return;

    int pos = partition(list, left, right);
    printf("%d", pos);
    quicksort(list, left, pos-1);
    quicksort(list, pos+1, right);
}

int partition(ArrayList<HiObject*>* list, int left, int right) {
    HiObject* pivot = list->get(left);
    int j = left+1;
    
    for (int i=left+1; i <= right; i++) {
        if (list->get(i)->le(pivot) == Universe::HiTrue) {
            swap(list, i, j++);
        }
    }
    swap(list, left, j-1);
    return j-1;
}

void swap(ArrayList<HiObject*>* list, int i, int j) {
    HiObject* a = list->get(i);
    list->set(i, list->get(j));
    list->set(j, a);
}

/*
    ListIteratorKlass and ListIterator
*/

ListIteratorKlass* ListIteratorKlass::instance = NULL;

ListIteratorKlass* ListIteratorKlass::get_instance() {
    if (instance == NULL)
        instance = new ListIteratorKlass();
    return instance;
}

ListIteratorKlass::ListIteratorKlass() {
    HiDict* _klass_dict = new HiDict();
    set_klass_dict(_klass_dict);
    set_name(new HiString("listiterator"));
}

ListIterator::ListIterator(HiList* owner) {
    _owner = owner;
    _iter_cnt = 0;
    set_klass(ListIteratorKlass::get_instance());
}

HiObject* ListIteratorKlass::next(HiObject* x) {
    ListIterator* i = (ListIterator* ) x;
    assert(i && i->klass() == (Klass*) this);

    HiList* list = i->owner();
    int iter_cnt = i->iter_cnt();
    if (iter_cnt < list->size()) {
        HiObject* obj = list->get(iter_cnt);
        i->inc_cnt();
        return obj;
    }
    else // TODO : we need StopIteration here to mask iteration end
        return NULL;
}