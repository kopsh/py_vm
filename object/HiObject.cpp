# include "object/HiObject.hpp"
# include "runtime/functionObject.hpp"
# include "runtime/universe.hpp"

void HiObject::print() {
    klass()->print(this);
}

void HiObject::repr() {
    klass()->repr(this);
}

HiObject* HiObject::greater(HiObject* rhs) {
    return klass()->greater(this, rhs);
}

HiObject* HiObject::less(HiObject* rhs) {
    return klass()->less(this, rhs);
}

HiObject* HiObject::equal(HiObject* rhs) {
    return klass()->equal(this, rhs);
}

HiObject* HiObject::not_equal(HiObject* rhs) {
    return klass()->not_equal(this, rhs);
}

HiObject* HiObject::ge(HiObject* rhs) {
    return klass()->ge(this, rhs);
}

HiObject* HiObject::le(HiObject* rhs) {
    return klass()->le(this, rhs);
}

HiObject* HiObject::add(HiObject* rhs) {
    return klass()->add(this, rhs);
}

HiObject* HiObject::sub(HiObject* rhs) {
    return klass()->sub(this, rhs);
}

HiObject* HiObject::mul(HiObject* rhs) {
    return klass()->mul(this, rhs);
}

HiObject* HiObject::div(HiObject* rhs) {
    return klass()->div(this, rhs);
}

HiObject* HiObject::mod(HiObject* rhs) {
    return klass()->mod(this, rhs);
}

HiObject* HiObject::len() {
    return klass()->len(this);
}

HiObject* HiObject::subscr(HiObject* x) {
    return klass()->subscr(this, x);
}

void HiObject::store_subscr(HiObject* x, HiObject* y) {
    klass()->store_subscr(this, x, y);
}

void HiObject::delete_subscr(HiObject* x) {
    klass()->delete_subscr(this, x);
}

HiObject* HiObject::contains(HiObject* x) {
    return klass()->contains(this, x);
}

HiObject* HiObject::contains_not(HiObject* x) {
    return klass()->contains_not(this, x);
}

HiObject* HiObject::iter() {
    return klass()->iter(this);
}

HiObject* HiObject::getattr(HiObject* x) {
    HiObject* res = Universe::HiNone;
    res = klass()->klass_dict()->get(x);

    if (MethodObject::is_function(res))
        res = new MethodObject(this, (FunctionObject* ) res);

    return res;
}
