# ifndef HILIST_HPP
# define HILIST_HPP

# include "object/HiObject.hpp"
# include "object/Klass.hpp"
# include "util/ArrayList.hpp"


class ListKlass : public Klass {
private:
    ListKlass();
    static ListKlass* instance;

public:
    static ListKlass* get_instance();
    virtual HiObject* allocate_instance(ObjList args);
    
    virtual void print(HiObject* x);
    virtual void repr(HiObject* x);
    virtual HiObject* subscr(HiObject* x, HiObject* y);
    virtual void store_subscr(HiObject* x, HiObject* y, HiObject* z);
    virtual void delete_subscr(HiObject* x, HiObject* y);
    virtual HiObject* contains(HiObject* x, HiObject* y);
    virtual HiObject* contains_not(HiObject* x, HiObject* y);
    virtual HiObject* iter(HiObject* x);
    virtual HiObject* add(HiObject* x, HiObject* y);
};

class HiList : public HiObject {
friend class ListKlass;
private:
    ObjList _inner_list;

public:
    HiList();
    HiList(ObjList ol);
    ObjList inner_list() {return _inner_list;}

    int size() { return _inner_list->size(); }
    void append(HiObject* obj) { _inner_list->append(obj); }
    HiObject* pop() { return _inner_list->pop(); }
    HiObject* get(int index) { return _inner_list->get(index); }
    void set(int i, HiObject* obj) { _inner_list->set(i, obj); }
    void insert(int i, HiObject* obj) { _inner_list->insert(i, obj); }
    HiObject* top() { return get(size()-1); }
    void delete_index(int i) { _inner_list->delete_index(i); }
};

class ListIteratorKlass : public Klass {
private:
    static ListIteratorKlass* instance;
    ListIteratorKlass();

public:
    static ListIteratorKlass* get_instance();
    virtual HiObject* next(HiObject* x);
};

class ListIterator : public HiObject {
private:
    HiList* _owner;
    int _iter_cnt;

public:
    ListIterator(HiList* owner);
    HiList* owner() {return _owner;}
    int iter_cnt() {return _iter_cnt;}
    void inc_cnt() {_iter_cnt++;}
};

HiObject* list_append(ObjList args);
HiObject* list_insert(ObjList args);
HiObject* list_index(ObjList args);
HiObject* list_pop(ObjList args);
HiObject* list_remove(ObjList args);
HiObject* list_reverse(ObjList args);
HiObject* list_sort(ObjList args);

void quicksort(ObjList list, int left, int right);
int partition(ObjList list, int left, int right);
void swap(ObjList list, int i, int j);

HiObject* listiterator_next(ObjList args);

# endif