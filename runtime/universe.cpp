# include "object/HiInteger.hpp"
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

    // initialize StringKlass
    HiDict* klass_dict = new HiDict();
    StringKlass::get_instance()->set_klass_dict(klass_dict);
    klass_dict->put(new HiString("upper"), new FunctionObject(string_upper));
}

void Universe::destory() {
    delete HiTrue;
    delete HiFalse;
    delete HiNone;
}