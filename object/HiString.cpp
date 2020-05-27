# include "HiString.hpp"
# include "string.h"

HiString::HiString(const char * x) {
    _length = strlen(x);
    _value = new char[_length];
    strcpy(_value, x);
}

HiString::HiString(const char * x, int length) {
    _length = length;
    _value = new char[_length];

    //since '\0' is allowed, don`t use strcpy
    memmove(_value, x, length);
}

const char* HiString::value() {
    return _value;
}

int HiString::length() {
    return _length;
}
