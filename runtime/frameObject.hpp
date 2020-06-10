# ifndef FRAMEOBJECT_HPP
# define FRAMEOBJECT_HPP

# include "code/CodeObject.hpp"
# include "util/ArrayList.hpp"
# include "util/Map.hpp"

class Block {
public:
    unsigned char _type; //循环类型
    unsigned int _target; //执行BREAK_LOOP之后的跳转地址
    int _level; // 进入Block时，操作栈的深度

    Block(unsigned char b_type, unsigned int b_target, int b_level):
        _type(b_type), _target(b_target), _level(b_level) {}

    Block() {
        _type = 0;
        _target = 0;
        _level = 0;
    }

    Block(const Block& b) {
        _type = b._type;
        _target = b._target;
        _level = b._level;
    }
};

class FunctionObject;

class FrameObject {
public:
    FrameObject(CodeObject* c);
    FrameObject(FunctionObject* fo, ObjList args);

    ObjList _stack;
    ArrayList<Block*>* _loop_stack;

    ObjList _consts;
    ObjList _names;

    Map<HiObject*, HiObject*>* _locals;
    Map<HiObject*, HiObject*>* _globals;
    ObjList _fast_locals;

    CodeObject* _codes;
    int _pc;

    FrameObject* _sender; // 记录调用者的栈帧，每调用一个新的栈帧，插入到链表头部，销毁时先销毁头结点，满足“后进先出”

public:
    void set_pc(int x) {_pc = x;}
    int get_pc() {return _pc;}

    ObjList stack() {return _stack;}
    ArrayList<Block*>* loop_stack() {return _loop_stack;}
    ObjList names() {return _names;}
    ObjList consts() {return _consts;}

    Map<HiObject*, HiObject*>* locals() {return _locals;}
    Map<HiObject*, HiObject*>* globals() {return _globals;}

    bool has_more_codes();
    unsigned char get_op_code();
    int get_op_arg();

    void set_sender(FrameObject* fo) {_sender = fo;}
    FrameObject* sender() {return _sender;}
    bool is_first_frame() {return _sender == NULL;}
};

# endif