# ifndef INTERPRETER_HPP
# define INTERPRETER_HPP

# include "code/byteCode.hpp"
# include "code/CodeObject.hpp"
# include "runtime/frameObject.hpp"

class Interpreter {
private:
    static Interpreter* _instance;
    Interpreter();

    FrameObject* _frame;
    HiObject* _ret_value;

    Map<HiObject*, HiObject*>* _builtins; // 只需维护一份builtin变量表

public:
    static Interpreter* get_instance();
    void run(CodeObject* code_object);

    void build_frame(HiObject* callable);
    void eval_frame();
    // void leave_frame();
    void destory_frame();
};

# endif