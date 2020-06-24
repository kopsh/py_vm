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

    virtual HiObject* subscr(HiObject* x, HiObject* y);
    // virtual HiObject* iter(HiObject* x);
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

HiObject* set_dict_default(ObjList args);
HiObject* dict_pop(ObjList args);

# endif