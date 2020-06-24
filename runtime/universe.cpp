# include "object/HiDict.hpp"
# include "object/HiInteger.hpp"
# include "object/HiList.hpp"
# include "object/HiString.hpp"
# include "runtime/universe.hpp"
# include "runtime/functionObject.hpp"

# include <string.h>

HiInteger* Universe::HiTrue = NULL;
HiInteger* Universe::HiFalse = NULL;
HiObject* Universe::HiNone = NULL;

void Universe::genesis() {
    HiTrue = new HiInteger(1);
    HiFalse = new HiInteger(0);
    HiNone = new HiObject();

    DictKlass::get_instance()->initialize();
    ListKlass::get_instance()->initialize();
    StringKlass::get_instance()->initialize();
}

void Universe::destory() {
    delete HiTrue;
    delete HiFalse;
    delete HiNone;
}