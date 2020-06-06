# ifndef INTERPRETER_HPP
# define INTERPRETER_HPP

# include "code/byteCode.hpp"
# include "code/CodeObject.hpp"

class Interpreter {
private:
    static Interpreter* _instance;
    Interpreter();
public:
    static Interpreter* get_instance();
    void run(CodeObject* code_object);
};

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

# endif