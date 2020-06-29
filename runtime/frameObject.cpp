# include "runtime/functionObject.hpp"
# include "runtime/frameObject.hpp"
# include "object/HiString.hpp"
# include "object/HiList.hpp"

# include <iostream>

// 初始化第一个FrameObject
// globals == locals
FrameObject::FrameObject(CodeObject* codes) {    
    _consts = codes->_consts;
    _names = codes->_names;

    _stack = new ArrayList<HiObject*>(codes->_stacksize);
    _loop_stack = new ArrayList<Block*>();

    _locals = new HiDict();
    _globals = _locals;
    _locals->put(new HiString("__name__"), new HiString("__main__"));
    _fast_locals = NULL;
    _closure = NULL;

    _codes = codes;
    _pc = 0;
    _entry_frame = false;

    _sender = NULL;
}

FrameObject::FrameObject(FunctionObject* func, ObjList args, int op_arg) {
    assert((args && op_arg != 0) || (!args && op_arg == 0));

    _codes = func->_func_code;
    _consts = _codes->_consts;
    _names = _codes->_names;

    _stack = new ArrayList<HiObject*>(_codes->_stacksize);
    _loop_stack = new ArrayList<Block*>();

    _locals = new HiDict();
    _globals = func->_globals;
    _fast_locals = new HiList();
    _closure = NULL;

    const int argcnt = _codes->_argcount; // 参数个数，不包括扩张位置参数和扩展键参数
    const int na = op_arg & 0xff; // 实际传入的位置参数个数
    const int nk = op_arg >> 8; // 实际传入的键参数个数
    int kw_pos = argcnt;

    /*
     处理默认参数
     def f(a, b, c=1, d=2):pass
     
     argcnt = 4 // 四个参数
     default = [1,2] 
     fast_locals = [NULL, NULL, 1, 2]

     调用f(1, 2, 3)
     fast_locals = [1, 2, 3, 2]
    */
    if (func->defaults()) {
        int dft_cnt = func->defaults()->length();
        int arg_cnt = _codes->_argcount;

        while (dft_cnt--) {
            _fast_locals->set(--arg_cnt, func->defaults()->get(dft_cnt));
        }
    }

    HiList* alist = NULL; // 存储 *args
    HiDict* adict = NULL; //     *kwargs
    
    if (argcnt < na) { // 存在*args, 即传入位置参数个数大于定义时用的位置参数个数
        int i = 0;
        for (; i < argcnt; i++)
            _fast_locals->set(i, args->get(i));

        alist = new HiList();
        for (; i < na; i++)
            alist->append(args->get(i));
    }
    else {
        for (int i=0; i < na; i++)
            _fast_locals->set(i, args->get(i));
    }

    // 当传入的参数不在code对象的参数列表中时，表明它是**kwargs中的参数
    for (int i=0; i < nk; i++) {
        HiObject* k = args->get(na + i*2);
        HiObject* v = args->get(na + i*2 + 1);

        int index = _codes->_var_names->index(k);
        if (index >= 0) {
            _fast_locals->set(index, v);
        }
        else {
            if (adict == NULL)
                adict = new HiDict();
            
            adict->put(k, v);
        }
    }

    if (_codes->_flag & FunctionObject::CO_VARARGS) {
        if (alist == NULL) {
            alist = new HiList();
        }
        _fast_locals->set(argcnt, alist);
        kw_pos++;
    }
    else {
        if (alist != NULL) {
            printf("takes more extend parameters!\n");
            assert(false);
        }
    }

    if (_codes->_flag & FunctionObject::CO_VARKEYWORDS) {
        if (adict == NULL) {
            adict = new HiDict();
        }
        _fast_locals->set(kw_pos, adict);
    }
    else {
        if (adict != NULL) {
            printf("takes more extend keyword parameters!\n");
            assert(false);
        }
    }
    
    // 打包cell变量（包括当前的cellvars和上层闭包打包好的cell变量）
    ArrayList<HiObject*>* cells = _codes->_cell_vals;
    if (cells && cells->size() > 0) {
        _closure = new HiList();

        for (int i = 0; i < cells->size(); i++) {
            _closure->append(NULL); // 占位，通过STORE_DEREF进行赋值
        }
    }

    if (func->closure() && func->closure()->size() > 0) {
        if (_closure == NULL)
            _closure = func->closure();
        else {
            _closure = (HiList*)_closure->add(func->closure());
        }
    }


    _pc = 0;
    _entry_frame = false;
    _sender = NULL;
}

int FrameObject::get_op_arg() {
    int byte1 = _codes->_bytecodes->value()[_pc++] & 0xff;
    int byte2 = _codes->_bytecodes->value()[_pc++] & 0xff;

    return byte2 << 8 | byte1;
}

unsigned char FrameObject::get_op_code() {
    return _codes->_bytecodes->value()[_pc++];
}

bool FrameObject::has_more_codes() {
    return _pc < _codes->_bytecodes->length();
}

HiObject* FrameObject::get_cell_from_parameter(int i) {
    HiObject* cell_name = _codes->_cell_vals->get(i);
    i = _codes->_var_names->index(cell_name);
    return _fast_locals->get(i);
}