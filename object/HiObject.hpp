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
    HiObject* getattr(HiObject* x);
    HiObject* contains(HiObject* x);
    HiObject* contains_not(HiObject* x);
};

# endif