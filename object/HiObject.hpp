# ifndef _HI_OBJECT_HPP
# define _HI_OBJECT_HPP

# include "assert.h"

# include "object/Klass.hpp"

class HiObject {
private:
    Klass* _klass;

public:
    Klass* klass() {
        assert(_klass != NULL);
        return _klass;
    }
    void set_klass(Klass* x) {_klass = x;}

    void print();
    void repr();
    HiObject* add(HiObject* x);
    HiObject* sub(HiObject* x);
    HiObject* mul(HiObject* x);
    HiObject* div(HiObject* x);
    HiObject* mod(HiObject* x);

    HiObject* greater(HiObject *x);
    HiObject* less(HiObject *x);
    HiObject* equal(HiObject *x);
    HiObject* not_equal(HiObject *x);
    HiObject* ge(HiObject *x);
    HiObject* le(HiObject *x);

    HiObject* len();
    HiObject* subscr(HiObject* x);
    void store_subscr(HiObject* x, HiObject* y);
    void delete_subscr(HiObject* x);
    HiObject* contains(HiObject* x);
    HiObject* contains_not(HiObject* x);

    HiObject* iter();
    HiObject* next();

    HiObject* getattr(HiObject* x);
};

class TypeKlass : public Klass {
private:
    TypeKlass();
    static TypeKlass* instance;

public:
    void initialize();
    static TypeKlass* get_instance();
    virtual void print(HiObject* x);
};

class HiTypeObject : public HiObject {
private:
    Klass* _own_klass;

public:
    HiTypeObject();
    void set_own_klass(Klass* k);
    Klass* own_klass() { return _own_klass; }
};


# endif