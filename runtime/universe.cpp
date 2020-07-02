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
 
    HiTypeObject* obj_obj = new HiTypeObject();
    obj_obj->set_own_klass(object_klass);

    TypeKlass::get_instance()->initialize();
    DictKlass::get_instance()->initialize();
    StringKlass::get_instance()->initialize();
    ListKlass::get_instance()->initialize();

    TypeKlass::get_instance()->order_supers();
    DictKlass::get_instance()->order_supers();
    StringKlass::get_instance()->order_supers();
    ListKlass::get_instance()->order_supers();
    IntegerKlass::get_instance()->order_supers();
    type_klass->order_supers();

    NativeFunctionKlass::get_instance()->order_supers();
    MethodKlass::get_instance()->order_supers();
    FunctionKlass::get_instance()->order_supers();

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