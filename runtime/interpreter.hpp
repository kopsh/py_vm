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

public:
    static Interpreter* get_instance();
    void run(CodeObject* code_object);
};

# endif