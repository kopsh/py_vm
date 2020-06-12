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
    virtual void print(HiObject* x);
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
};

# endif