# include "object/HiInteger.hpp"
# include "object/HiString.hpp"
# include "runtime/interpreter.hpp"
# include "util/ArrayList.hpp"
# include "code/CodeObject.hpp"

# include <string.h>
# include <iostream>

# define PUSH(x) _stack->append((x))
# define POP() _stack->pop()


Interpreter* Interpreter::_instance = NULL;

Interpreter* Interpreter::get_instance() {
    if (_instance == NULL) {
        _instance = new Interpreter();
    }

    return _instance;
}

Interpreter::Interpreter() {

}

void Interpreter::run(CodeObject* codes) {
    int pc = 0;
    int code_length = codes->_bytecodes->length();
    

    ArrayList<HiObject*>* _stack = new ArrayList<HiObject*>(codes->_stacksize);
    ArrayList<HiObject*>* _consts = codes->_consts;

    while (pc < code_length) {
        unsigned char op_code = codes->_bytecodes->value()[pc++];
        bool has_argument = (op_code & 0xFF) >= ByteCode::HAVE_ARGUMENT; // 操作数大于90，表示带参数

        int op_arg = -1;
        if (has_argument) {
            int byte1 = (codes->_bytecodes->value()[pc++]) & 0xFF;
            op_arg = ((codes->_bytecodes->value()[pc++]) & 0xFF) << 8 | byte1;
        }

        // HiInteger *lhs, *rhs;
        HiObject *u, *w, *v, *attr;

        switch (op_code)
        {
            case ByteCode::LOAD_CONST:
                PUSH(_consts->get(op_arg));
                break;

            case ByteCode::PRINT_ITEM:
                v = POP();
                v->print();
                break;

            case ByteCode::PRINT_NEWLINE:
                printf("\n");
                break;
            
            case ByteCode::BINARY_ADD:
                v = POP();
                w = POP();
                PUSH(w->add(v));
                break;

            case ByteCode::RETURN_VALUE:
                POP();
                break;

            default:
                printf("Error: Unrecognized byte code %d\n", op_code);
        } 
    }
}