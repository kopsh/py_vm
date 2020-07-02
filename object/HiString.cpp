# include "object/HiDict.hpp"
# include "object/HiString.hpp"
# include "runtime/functionObject.hpp"
# include "runtime/universe.hpp"
# include "util/ArrayList.hpp"

# include "string.h"
# include <iostream>

StringKlass* StringKlass::instance = NULL;

StringKlass* StringKlass::get_instance() {
    if (instance == NULL)
        instance = new StringKlass();

    return instance;
}

void StringKlass::initialize() {
    (new HiTypeObject())->set_own_klass(this);

    set_name(new HiString("str"));
    HiDict* klass_dict = new HiDict();
    klass_dict->put(new HiString("upper"), new FunctionObject(string_upper));
    set_klass_dict(klass_dict);

    set_name(new HiString("str"));
    add_super(ObjectKlass::get_instance());
}

HiString::HiString(const char * x) {
    _length = strlen(x);
    _value = new char[_length];
    strcpy(_value, x);

    set_klass(StringKlass::get_instance());
}

HiString::HiString(const char * x, int length) {
    _length = length;
    _value = new char[_length];

    //since '\0' is allowed, don`t use strcpy
    memmove(_value, x, length);

    set_klass(StringKlass::get_instance());
}

const char* HiString::value() {
    return _value;
}

int HiString::length() {
    return _length;
}

HiObject* StringKlass::equal(HiObject* x, HiObject* y) {
    if (x->klass() != y->klass())
        return Universe::HiFalse;

    HiString* sx = (HiString* ) x;
    HiString* sy = (HiString* ) y;

    assert(sx && sx->klass() == (Klass* )this);
    assert(sy && sy->klass() == (Klass* )this);

    if (sx->length() != sy->length())
        return Universe::HiFalse;

    for (int i=0; i < sx->length(); i++) {
        if (sx->value()[i] != sy->value()[i])
            return Universe::HiFalse;
    }

    return Universe::HiTrue;
}

HiObject* StringKlass::less(HiObject* x, HiObject* y) {
     if (x->klass() != y->klass()) {
        if (Klass::compare_klass(x->klass(), y->klass()) < 0)
            return Universe::HiTrue;
        else
            return Universe::HiFalse;
    }

    HiString* sx = (HiString* ) x;
    HiString* sy = (HiString* ) y;

    assert(sx && sx->klass() == (Klass* )this);
    assert(sy && sy->klass() == (Klass* )this);

    int len = sx->length() < sy->length() ? sx->length() : sy->length();


    for (int i=0; i < len; i++) {
        if (sx->value()[i] < sy->value()[i])
            return Universe::HiTrue;
        if (sx->value()[i] > sy->value()[i])
            return Universe::HiFalse;
    }

    if (sx->length() < sy->length())
        return Universe::HiTrue;

    return Universe::HiFalse;
}

void StringKlass::print(HiObject* obj) {
    HiString* sobj = (HiString* )obj;
    assert(sobj && sobj->klass() == (Klass*) this);

    for (int i=0; i < sobj->length(); i++)
        printf("%c", sobj->value()[i]);
}

void StringKlass::repr(HiObject* obj) {
    HiString* sobj = (HiString* )obj;
    assert(sobj && sobj->klass() == (Klass*) this);

    printf("\'");
    sobj->print();
    printf("\'");
}


HiObject* StringKlass::len(HiObject* x) {
    return new HiInteger(((HiString* )x)->length());
}

HiObject* string_upper(ObjList args) {
    HiObject* arg0 = args->get(0);

    assert(arg0->klass() == StringKlass::get_instance());

    HiString* s = (HiString* )arg0;
    int length = s->length();

    if (length <= 0)
        return Universe::HiNone;

    char* v = new char[length];
    char c;
    for (int i=0; i < length; i++) {
        c = s->value()[i];
        if ('a' <= c && 'z' >= c)
            v[i] = c - 0x20;
        else
            v[i] = c;
    }

    HiString* res = new HiString(v, length);
    delete[] v;
    return res; 
}

HiObject* StringKlass::subscr(HiObject* x, HiObject* y) {
    assert(x && x->klass() == StringKlass::get_instance());
    assert(y && y->klass() == IntegerKlass::get_instance());

    HiString* sx = (HiString* ) x;
    HiInteger* iy = (HiInteger* ) y;

    return new HiString(&(sx->value()[iy->value()]), 1);
}

HiObject* StringKlass::allocate_instance(HiObject* callable, ArrayList<HiObject*>* args) {
    if (!args || args->length() == 0)
        return new HiString("");
    else
        return NULL;
}