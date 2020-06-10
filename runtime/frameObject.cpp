# include "runtime/functionObject.hpp"
# include "runtime/frameObject.hpp"
# include "object/HiString.hpp"

FrameObject::FrameObject(CodeObject* codes) {
    _consts = codes->_consts;
    _names = codes->_names;

    _stack = new ArrayList<HiObject*>(codes->_stacksize);
    _loop_stack = new ArrayList<Block*>();

    _locals = new Map<HiObject*, HiObject*>();
    _globals = _locals;

    _codes = codes;
    _pc = 0;

    _sender = NULL;
}

FrameObject::FrameObject(FunctionObject* func, ObjList args) {
    _codes = func->_func_code;
    _consts = _codes->_consts;
    _names = _codes->_names;

    _stack = new ArrayList<HiObject*>(_codes->_stacksize);
    _loop_stack = new ArrayList<Block*>();

    _locals = new Map<HiObject*, HiObject*>();
    _globals = func->_globals;

    _fast_locals = new ArrayList<HiObject*>();

    if (func->defaults()) {
        int dft_cnt = func->defaults()->length();
        int arg_cnt = _codes->_argcount;

        while (dft_cnt--) {
            _fast_locals->set(--arg_cnt, func->defaults()->get(dft_cnt));
        }
    }

    if (args) {
        for (int i=0; i < args->length(); i++)
            _fast_locals->set(i, args->get(i));
    }

    _pc = 0;
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
