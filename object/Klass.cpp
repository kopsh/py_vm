# include "object/Klass.hpp"
# include "object/HiInteger.hpp"
# include "object/HiString.hpp"
# include "object/HiDict.hpp"
# include "object/HiList.hpp"
# include "runtime/functionObject.hpp"
# include "runtime/interpreter.hpp"
# include "runtime/Table.hpp"
# include "runtime/universe.hpp"

# include "assert.h"
# include "stdio.h"

#define ST(x) StringTable::get_instance()->STR(x)
#define STR(x) x##_str

Klass::Klass() {
    _super = NULL;
    _mro = NULL;
    _builtin = true;
}

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
    new_klass->set_super_list(supers_list);
    new_klass->order_supers();

    HiTypeObject* type_obj = new HiTypeObject();
    type_obj->set_own_klass(new_klass);

    return type_obj;
}

HiObject* Klass::allocate_instance(HiObject* callable, ArrayList<HiObject*>* args) {
    HiObject* inst = new HiObject();
    inst->set_klass(((HiTypeObject*)callable)->own_klass());
    HiObject* constructor = inst->getattr(StringTable::get_instance()->init_str);
    if (constructor != Universe::HiNone) {
        Interpreter::get_instance()->call_virtual(constructor, args);
    }
    return inst;
}

HiObject* Klass::setattr(HiObject* x, HiObject* y, HiObject* z) {
    HiObject* func = x->klass()->klass_dict()->get(ST(setattr));
    if (func != Universe::HiNone) {
        func = new MethodObject((FunctionObject*) func);
        ObjList args = new ArrayList<HiObject*>();
        args->append(y);
        args->append(z);
        return Interpreter::get_instance()->call_virtual(func, args);
    }

    if (x->obj_dict() == NULL) {
        x->set_obj_dict(new HiDict());
    }

    x->obj_dict()->put(y, z);
    return Universe::HiNone;
}

HiObject* Klass::getattr(HiObject* x, HiObject* y) {
    HiObject* func = find_in_parents(x, ST(getattr));
    if (func != Universe::HiNone) {
        func = new MethodObject((FunctionObject*) func);
        ObjList args = new ArrayList<HiObject*>();
        args->append(y);
        return Interpreter::get_instance()->call_virtual(func, args);
    }

    HiObject* res = Universe::HiNone;
    if (x->obj_dict() != NULL) {
        res = x->obj_dict()->get(y);
        if (res != Universe::HiNone)
            return res;
    }

    res = find_in_parents(x, y);
    if (res != Universe::HiNone && MethodObject::is_function(res))
        res = new MethodObject(x, (FunctionObject* ) res);

    return res;
}

HiObject* Klass::find_in_parents(HiObject* x, HiObject* y) {
    HiObject* result = Universe::HiNone;
    result = x->klass()->klass_dict()->get(y);

    if (result != Universe::HiNone) {
        return result;
    }

    // find attribute in all parents.
    if (x->klass()->mro() == NULL)
        return result;

    for (int i = 0; i < x->klass()->mro()->size(); i++) {
        result = ((HiTypeObject*)(x->klass()->mro()->get(i)))
                 ->own_klass()->klass_dict()->get(y);

        if (result != Universe::HiNone)
            break;
    }

    return result;
}

void Klass::add_super(Klass* x) {
    if (x == NULL)
        return;

    if (_super == NULL)
        _super = new HiList();
    
    _super->append(x->type_object());
}

void Klass::order_supers() {
    if (_super == NULL)
        return;

    if (_mro == NULL)
        _mro = new HiList();

    for (int i=0; i < _super->size(); i++) {
        HiTypeObject* _tp_obj = (HiTypeObject*)(_super->get(i));
        Klass* k = _tp_obj->own_klass();
        _mro->append(_tp_obj);
        if (k->mro() == NULL) 
            continue;
        
        for (int j=0; j < k->mro()->size(); j++) {
            HiTypeObject* _tp_obj = (HiTypeObject*) (k->mro()->get(j));
            int index = _mro->index(_tp_obj);
            if (index >= 0)
                _mro->delete_index(index);
            _mro->append(_tp_obj);
        }
    }
}

HiObject* Klass::find_and_call(HiObject* lhs, ObjList args, HiObject* func_name) {
    HiObject* func = lhs->getattr(func_name);
    if (func != Universe::HiNone) {
        return Interpreter::get_instance()->call_virtual(func, args);
    }

    printf("class ");
    lhs->klass()->name()->print();
    printf(" Error : unsupport operation for class ");
    assert(false);
    return Universe::HiNone;
}

HiObject* Klass::add(HiObject* x, HiObject* y) {
    ObjList args = new ArrayList<HiObject*>();
    args->append(y);
    return find_and_call(x, args, StringTable::get_instance()->add_str);
}

HiObject* Klass::len(HiObject* x) {
    return find_and_call(x, NULL, ST(len));
}

HiObject* Klass::getitem(HiObject* x, HiObject* y) {
    ObjList args = new ArrayList<HiObject*>();
    args->append(y);
    return find_and_call(x, args, ST(getitem));
}

HiObject* Klass::setitem(HiObject* x, HiObject* y, HiObject* z) {
    ObjList args = new ArrayList<HiObject*>();
    args->append(y);
    args->append(z);
    return find_and_call(x, args, ST(setitem));
}