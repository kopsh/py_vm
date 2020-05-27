# include "object/HiInteger.hpp"

# include <iostream>

HiInteger::HiInteger(int x) {
    _value = x;
}

void HiInteger::print() {
    printf("%d", _value);
}

HiObject* HiInteger::add(HiObject* x) {
    return new HiInteger(_value + ((HiInteger* )x)->_value);
}
