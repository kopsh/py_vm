# include "object/HiInteger.hpp"
# include "runtime/universe.hpp"

# include <iostream>

class IntegerKlass;

IntegerKlass* IntegerKlass::instance = NULL;

IntegerKlass::IntegerKlass() {

}

IntegerKlass* IntegerKlass::get_instance() {
    if (instance == NULL) {
        instance = new IntegerKlass();
    }

    return instance;
}

HiInteger::HiInteger(int x) {
    _value = x;
    set_klass(IntegerKlass::get_instance());
}

void IntegerKlass::print(HiObject* x) {
    HiInteger* ix = (HiInteger* ) x;

    printf("%d", ix->value());
}

void IntegerKlass::repr(HiObject* x) {
    HiInteger* ix = (HiInteger* ) x;

    printf("%d", ix->value());
}

HiObject* IntegerKlass::greater(HiObject* x, HiObject* y) {
    if (x->klass() != y->klass())
        return Universe::HiFalse;

    HiInteger* ix = (HiInteger* ) x;
    HiInteger* iy = (HiInteger* ) y;

    assert(ix && (ix->klass() == (Klass* ) this));
    assert(iy && (iy->klass() == (Klass* ) this));

    if (ix->value() > iy->value())
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* IntegerKlass::less(HiObject* x, HiObject* y) {
    if (x->klass() != y->klass()) {
        if (Klass::compare_klass(x->klass(), y->klass()) < 0)
            return Universe::HiTrue;
        else
            return Universe::HiFalse;
    }

    HiInteger* ix = (HiInteger* ) x;
    HiInteger* iy = (HiInteger* ) y;

    assert(ix && (ix->klass() == (Klass* ) this));
    assert(iy && (iy->klass() == (Klass* ) this));

    if (ix->value() < iy->value())
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* IntegerKlass::equal(HiObject* x, HiObject* y) {
    if (x->klass() != y->klass())
        return Universe::HiFalse;

    HiInteger* ix = (HiInteger* ) x;
    HiInteger* iy = (HiInteger* ) y;

    assert(ix && (ix->klass() == (Klass* ) this));
    assert(iy && (iy->klass() == (Klass* ) this));

    if (ix->value() == iy->value())
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* IntegerKlass::not_equal(HiObject* x, HiObject* y) {
    if (x->klass() != y->klass())
        return Universe::HiFalse;

    HiInteger* ix = (HiInteger* ) x;
    HiInteger* iy = (HiInteger* ) y;

    assert(ix && (ix->klass() == (Klass* ) this));
    assert(iy && (iy->klass() == (Klass* ) this));

    if (ix->value() != iy->value())
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* IntegerKlass::ge(HiObject* x, HiObject* y) {
    if (x->klass() != y->klass())
        return Universe::HiFalse;

    HiInteger* ix = (HiInteger* ) x;
    HiInteger* iy = (HiInteger* ) y;

    assert(ix && (ix->klass() == (Klass* ) this));
    assert(iy && (iy->klass() == (Klass* ) this));

    if (ix->value() >= iy->value())
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* IntegerKlass::le(HiObject* x, HiObject* y) {
    if (x->klass() != y->klass())
        return Universe::HiFalse;

    HiInteger* ix = (HiInteger* ) x;
    HiInteger* iy = (HiInteger* ) y;

    assert(ix && (ix->klass() == (Klass* ) this));
    assert(iy && (iy->klass() == (Klass* ) this));

    if (ix->value() <= iy->value())
        return Universe::HiTrue;
    else
        return Universe::HiFalse;
}

HiObject* IntegerKlass::add(HiObject* x, HiObject* y) {
    if (x->klass() != y->klass())
        return Universe::HiNone;

    HiInteger* ix = (HiInteger* ) x;
    HiInteger* iy = (HiInteger* ) y;

    assert(ix && (ix->klass() == (Klass* ) this));
    assert(iy && (iy->klass() == (Klass* ) this));

    return new HiInteger(ix->value() + iy->value());
}

HiObject* IntegerKlass::sub(HiObject* x, HiObject* y) {
    if (x->klass() != y->klass())
        return Universe::HiNone;

    HiInteger* ix = (HiInteger* ) x;
    HiInteger* iy = (HiInteger* ) y;

    assert(ix && (ix->klass() == (Klass* ) this));
    assert(iy && (iy->klass() == (Klass* ) this));

    return new HiInteger(ix->value() - iy->value());
}

HiObject* IntegerKlass::mul(HiObject* x, HiObject* y) {
    if (x->klass() != y->klass())
        return Universe::HiNone;

    HiInteger* ix = (HiInteger* ) x;
    HiInteger* iy = (HiInteger* ) y;

    assert(ix && (ix->klass() == (Klass* ) this));
    assert(iy && (iy->klass() == (Klass* ) this));

    return new HiInteger(ix->value() * iy->value());
}

HiObject* IntegerKlass::div(HiObject* x, HiObject* y) {
    if (x->klass() != y->klass())
        return Universe::HiNone;

    HiInteger* ix = (HiInteger* ) x;
    HiInteger* iy = (HiInteger* ) y;

    assert(ix && (ix->klass() == (Klass* ) this));
    assert(iy && (iy->klass() == (Klass* ) this));
    assert(iy->value() != 0);

    return new HiInteger(ix->value() / iy->value());
}

HiObject* IntegerKlass::mod(HiObject* x, HiObject* y) {
    if (x->klass() != y->klass())
        return Universe::HiNone;

    HiInteger* ix = (HiInteger* ) x;
    HiInteger* iy = (HiInteger* ) y;

    assert(ix && (ix->klass() == (Klass* ) this));
    assert(iy && (iy->klass() == (Klass* ) this));
    assert(iy->value() != 0);

    return new HiInteger(ix->value() % iy->value());
}