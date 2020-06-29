# include "object/Klass.hpp"
# include "object/HiInteger.hpp"
# include "object/HiString.hpp"
# include "object/HiDict.hpp"
# include "object/HiList.hpp"
# include "runtime/functionObject.hpp"
# include "runtime/universe.hpp"

# include "assert.h"

int Klass::compare_klass(Klass* x, Klass* y) {
    if (x == y)
        return 0;

    if (x == IntegerKlass::get_instance())
        return -1;
    else if (y == IntegerKlass::get_instance())
        return 1;
    
    if (x->name()->less(y->name()) == Universe::HiTrue)
        return -1;
    else
        return 1;
}

HiObject* Klass::create_klass(HiObject* dict, HiObject* supers, HiObject* name) {
    assert(dict->klass() == (Klass*) DictKlass::get_instance());
    assert(supers->klass() == (Klass*) ListKlass::get_instance());
    assert(name->klass() == (Klass*) StringKlass::get_instance());

    Klass* new_klass = new Klass();
    new_klass->set_builtin(false);
    HiDict* klass_dict = (HiDict*) dict;
    HiList* supers_list = (HiList*) supers;
    
    new_klass->set_klass_dict(klass_dict);
    new_klass->set_name((HiString*) name);
    if (supers_list->size() > 0) {
        HiTypeObject* super = (HiTypeObject*) supers_list->get(0);
        new_klass->set_super(super->own_klass());
    }

    HiTypeObject* type_obj = new HiTypeObject();
    type_obj->set_own_klass(new_klass);

    return type_obj;
}

HiObject* Klass::allocate_instance(HiObject* callable, ArrayList<HiObject*>* args) {
    HiObject* inst = new HiObject();
    inst->set_klass(((HiTypeObject*)callable)->own_klass());
    return inst;
}

HiObject* Klass::setattr(HiObject* x, HiObject* y, HiObject* z) {
    if (x->obj_dict() == NULL) {
        x->set_obj_dict(new HiDict());
    }

    x->obj_dict()->put(y, z);
    return Universe::HiNone;
}

HiObject* Klass::getattr(HiObject* x, HiObject* y) {
    HiObject* res = Universe::HiNone;
    if (x->obj_dict() != NULL) {
        res = x->obj_dict()->get(y);
        if (res != Universe::HiNone)
            return res;
    }

    res = x->klass()->klass_dict()->get(y);
    if (res == Universe::HiNone)
        return res;

    if (MethodObject::is_function(res))
        res = new MethodObject(x, (FunctionObject* ) res);

    return res;
}