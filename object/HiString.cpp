# include "HiString.hpp"
# include "runtime/universe.hpp"

# include "string.h"
# include <iostream>

StringKlass* StringKlass::instance = NULL;

StringKlass* StringKlass::get_instance() {
    if (instance == NULL)
        instance = new StringKlass();

    return instance;
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

void StringKlass::print(HiObject* obj) {
    HiString* sobj = (HiString* )obj;
    assert(sobj && sobj->klass() == (Klass*) this);

    for (int i=0; i < sobj->length(); i++)
        printf("%c", sobj->value()[i]);
}