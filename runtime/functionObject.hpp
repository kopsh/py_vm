# ifndef FUNCTION_OBJECT_HPP
# define FUNCTION_OBJECT_HPP

# include "code/CodeObject.hpp"
# include "object/Klass.hpp"
# include "runtime/frameObject.hpp"

class FunctionKlass : public Klass {
private:
    FunctionKlass();
    static FunctionKlass* instance;

public:
    static FunctionKlass* get_instance();
    virtual void print(HiObject* obj);
};

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
    
    Map<HiObject*, HiObject*>* _globals;    

    unsigned int _flags;

public:
    FunctionObject(HiObject* code_object);
    // FunctionObject(Klass* klass) {
    //     _func_code = NULL;
    //     _func_name = NULL;
    //     _flags = 0;

    //     set_class(klass);
    // }

    HiString* func_name() {return _func_name;}
    void set_globals(Map<HiObject*, HiObject*>* x) {_globals = x;}
    Map<HiObject*, HiObject*>* globals() {return _globals;}
    int flags() {return _flags;}
};

# endif