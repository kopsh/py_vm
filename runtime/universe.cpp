# include "runtime/universe.hpp"
# include "object/HiInteger.hpp"

# include <string.h>

HiInteger* Universe::HiTrue = NULL;
HiInteger* Universe::HiFalse = NULL;
HiObject* Universe::HiNone = NULL;

void Universe::genesis() {
    HiTrue = new HiInteger(1);
    HiFalse = new HiInteger(0);

    HiNone = new HiObject();
}

void Universe::destory() {
    delete HiTrue;
    delete HiFalse;
    delete HiNone;
}