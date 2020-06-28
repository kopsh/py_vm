# ifndef FUNCTION_OBJECT_HPP
# define FUNCTION_OBJECT_HPP

# include "code/CodeObject.hpp"
# include "object/Klass.hpp"
# include "object/HiList.hpp"
# include "runtime/frameObject.hpp"

class FunctionKlass : public Klass {
private:
    FunctionKlass();
    static FunctionKlass* instance;

public:
    static FunctionKlass* get_instance();
    virtual void print(HiObject* obj);
};

class NativeFunctionKlass : public Klass {
private:
    NativeFunctionKlass();
    static NativeFunctionKlass* instance;

public:
    static NativeFunctionKlass* get_instance();
};

HiObject* len(ObjList args);
HiObject* isinstance(ObjList args);
HiObject* type_of(ObjList args);
typedef HiObject* (*NativeFuncPointer)(ObjList args);

class FunctionObject : public HiObject {
friend class FunctionKlass;
friend class FrameObject;

private:
    CodeObject* _func_code;
    HiString* _func_name;
    
    /*
        函数依赖的全局变量是MAKE_FUNCTION的时候，而不是CALL_FUNCTION的时候，即函数定义的时候，全局变量即进行绑定

        # a.py
        from b import foo
        x = 100
        foo()

        # b.py
        x = 2
        def foo():
            print x

        >>> 2

        因此，functionObject需要自己的globals表
    */
    
    HiDict* _globals; // 全局变量，函数定义时进行绑定
    ObjList _defaults; // 默认参数列表， def foo(a, b, c=1, d=2):pass
    NativeFuncPointer _native_func; // 函数指针, 指向要实现的native函数
    HiList* _closure; // cell变量列表

    unsigned int _flags;

public:
    enum CO_FLAGS {
        CO_VARARGS = 0x4,
        CO_VARKEYWORDS = 0x8,
    };

    FunctionObject(HiObject* code_object);
    FunctionObject(NativeFuncPointer nfp);

    FunctionObject(Klass* klass) {
        _func_code = NULL;
        _func_name = NULL;
        _flags = 0;
        _defaults = NULL;

        set_klass(klass);
    }

    HiString* func_name() {return _func_name;}
    void set_globals(HiDict* x) {_globals = x;}
    HiDict* globals() {return _globals;}
    int flags() {return _flags;}
    void set_defaults(ObjList x);
    ObjList defaults() {return _defaults;}
    HiObject* call(ObjList args);
    HiList* closure() {return _closure;}
    void set_closure(HiList* x) { _closure=x;}
};

class MethodKlass : public Klass {
private:
    MethodKlass();
    static MethodKlass* instance;

public:
    static MethodKlass* get_instance();
};

class MethodObject : public HiObject {
friend class MethodKlass;

private:
    HiObject* _owner;
    FunctionObject* _func;

public:
    MethodObject(FunctionObject* func): _owner(NULL), _func(func) {
        set_klass(MethodKlass::get_instance());
    }

    MethodObject(HiObject* owner, FunctionObject* func): _owner(owner), _func(func) {
        set_klass(MethodKlass::get_instance());
    }
    
    HiObject* owner() {return _owner;}
    void set_owner(HiObject* owner) {_owner = owner;}
    FunctionObject* func() {return _func;}

    static bool is_function(HiObject* x);
};

# endif