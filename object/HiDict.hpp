# ifndef HIDICT_HPP
# define HIDICT_HPP

# include "object/HiObject.hpp"
# include "object/Klass.hpp"
# include "util/ArrayList.hpp"
# include "util/Map.hpp"

class DictKlass : public Klass {
private:
    DictKlass();
    static DictKlass* instance;

public:
    static DictKlass* get_instance();
    void initialize();
    virtual HiObject* allocate_instance(ObjList args);

    virtual HiObject* subscr(HiObject* x, HiObject* y);
    virtual HiObject* iter(HiObject* x);
    virtual void print(HiObject* x);
    virtual void repr(HiObject* x);
    virtual void store_subscr(HiObject* x, HiObject* y, HiObject* z);
    virtual void delete_subscr(HiObject*, HiObject*);

};

class HiDict : public HiObject {
friend class DictKlass;
private:
    ObjMap _map;

public:
    HiDict();
    HiDict(ObjMap map);
    ObjMap map() {return _map;}
    void put(HiObject* k, HiObject* v) { return _map->put(k, v); }
    HiObject* get(HiObject* k) { return _map->get(k); }
    HiObject* remove(HiObject* k) { return _map->remove(k); }
    int index(HiObject* k) { return _map->index(k); }
    bool has_key(HiObject* k) { return _map->has_key(k); }
    int size() { return _map->size(); }
};

class DictIterator : public HiObject {
private:
    HiDict* _owner;
    int _iter_cnt;

public:
    DictIterator(HiDict* owner);
    HiDict* owner() {return _owner;}
    int iter_cnt() {return _iter_cnt;}
    void inc_cnt() {_iter_cnt++;}
};

enum ITER_TYPE {
    ITER_KEY = 0,
    ITER_VALUE,
    ITER_ITEM
};

template <ITER_TYPE n>
class DictIteratorKlass : public Klass {
private:
    static DictIteratorKlass* instance;
    DictIteratorKlass();

public:
    static DictIteratorKlass* get_instance();
    virtual HiObject* iter(HiObject* x) {return x;} // 自身已经是迭代器对象
    virtual HiObject* next(HiObject* x);
};

HiObject* set_dict_default(ObjList args);
HiObject* dict_pop(ObjList args);
HiObject* dict_iterkeys(ObjList args);
HiObject* dict_itervalues(ObjList args);
HiObject* dict_iteritems(ObjList args);

# endif