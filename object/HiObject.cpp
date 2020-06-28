# include "object/HiObject.hpp"
# include "runtime/functionObject.hpp"
# include "runtime/Table.hpp"
# include "runtime/universe.hpp"

# include <iostream>

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

HiObject* HiObject::next() {
    return klass()->next(this);
}


HiObject* HiObject::getattr(HiObject* x) {
    HiObject* res = Universe::HiNone;
    res = klass()->klass_dict()->get(x);

    if (MethodObject::is_function(res))
        res = new MethodObject(this, (FunctionObject* ) res);

    return res;
}

/*
 * TypeKlass and HiTypeObject
 */

TypeKlass* TypeKlass::instance = NULL;

TypeKlass* TypeKlass::get_instance() {
    if (instance == NULL)
        instance = new TypeKlass();

    return instance;
}

TypeKlass::TypeKlass() {

}

void TypeKlass::initialize() {
    (new HiTypeObject())->set_own_klass(this);
    set_name(new HiString("type"));
}

void TypeKlass::print(HiObject* x) {
    assert(x->klass() == (Klass* ) this);
    printf("<type ");
    Klass* own_klass = ((HiTypeObject*) x)->own_klass();

    HiDict* attr_dict = own_klass->klass_dict();
    if (attr_dict) {
        HiObject* mod = attr_dict->get(StringTable::get_instance()->mod_str);
        if (mod != Universe::HiNone) {
            mod->print();
            printf(".");
        }
    }
    own_klass->name()->print();
    printf(">");
}

HiTypeObject::HiTypeObject() {
    set_klass(TypeKlass::get_instance());
}

void HiTypeObject::set_own_klass(Klass* k) {
    _own_klass = k;
    k->set_type_object(this);
}