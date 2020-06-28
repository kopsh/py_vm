# include "object/HiDict.hpp"
# include "object/HiInteger.hpp"
# include "object/HiList.hpp"
# include "object/HiString.hpp"
# include "runtime/universe.hpp"
# include "runtime/functionObject.hpp"

# include <string.h>

HiObject* Universe::HiTrue = NULL;
HiObject* Universe::HiFalse = NULL;
HiObject* Universe::HiNone = NULL;

void Universe::genesis() {
    HiTrue = new HiString("True");
    HiFalse = new HiString("False");
    HiNone = new HiObject();

    Klass* object_klass = ObjectKlass::get_instance();
    Klass* type_klass = TypeKlass::get_instance();

    HiTypeObject* tp_obj = new HiTypeObject();
    tp_obj->set_own_klass(type_klass);
    type_klass->set_super(object_klass);

    HiTypeObject* obj_obj = new HiTypeObject();
    obj_obj->set_own_klass(object_klass);
    object_klass->set_super(NULL);

    TypeKlass::get_instance()->initialize();
    DictKlass::get_instance()->initialize();
    StringKlass::get_instance()->initialize();

    type_klass->set_klass_dict(new HiDict());
    object_klass->set_klass_dict(new HiDict());

    type_klass->set_name(new HiString("type"));
    object_klass->set_name(new HiString("object"));
}

void Universe::destory() {
    delete HiTrue;
    delete HiFalse;
    delete HiNone;
}