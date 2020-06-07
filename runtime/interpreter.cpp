# include "code/CodeObject.hpp"
# include "object/HiInteger.hpp"
# include "object/HiString.hpp"
# include "runtime/interpreter.hpp"
# include "runtime/universe.hpp"
# include "util/ArrayList.hpp"
# include "util/Map.hpp"

# include <string.h>
# include <iostream>

# define PUSH(x) _frame->stack()->append((x))
# define POP() _frame->stack()->pop()
# define STACK_LEVEL() _frame->stack()->size()


Interpreter* Interpreter::_instance = NULL;

Interpreter* Interpreter::get_instance() {
    if (_instance == NULL) {
        _instance = new Interpreter();
    }

    return _instance;
}

Interpreter::Interpreter() {
    _frame = NULL;
}

void Interpreter::run(CodeObject* codes) {
    _frame = new FrameObject(codes);
    
    Block* b;
    int op_arg;
    unsigned char op_code;
    bool has_argument;

    while (_frame->has_more_codes()) 
    {
        op_code = _frame->get_op_code();
        has_argument = (op_code & 0xFF) >= ByteCode::HAVE_ARGUMENT; // 操作数大于90，表示带参数

        if (has_argument) {
            op_arg = _frame->get_op_arg();
        }

        // HiInteger *lhs, *rhs;
        HiObject *u, *w, *v, *attr;

        switch (op_code)
        {
            case ByteCode::LOAD_CONST:
                PUSH(_frame->consts()->get(op_arg));
                break;

            case ByteCode::STORE_NAME:
                v = _frame->names()->get(op_arg);
                _frame->locals()->put(v, POP());
                break;
            
            case ByteCode::LOAD_NAME:
                v = _frame->names()->get(op_arg);
                PUSH(_frame->locals()->get(v));
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

            case ByteCode::COMPARE_OF:
                v = POP();
                w = POP();

                switch (op_arg)
                {
                    case ByteCode::GREATER:
                        PUSH(w->greater(v));
                        break;
                    
                    case ByteCode::LESS:
                        PUSH(w->less(v));
                        break;
                    
                    case ByteCode::EQUAL:
                        PUSH(w->equal(v));
                        break;

                    case ByteCode::NOT_EQUAL:
                        PUSH(w->not_equal(v));
                        break;
                    
                    case ByteCode::GREATER_EQUAL:
                        PUSH(w->ge(v));
                        break;

                    case ByteCode::LESS_EQUAL:
                        PUSH(w->le(v));
                        break;

                    default:
                        printf("Error: unrecognized compare op %d\n", op_arg);
                }
                break;

            case ByteCode::POP_JUMP_IF_FALSE:
            /*
                if 1 > 2:
                    print 2
                else:
                    print 1

                1           0 LOAD_CONST               0 (2)
                            3 LOAD_CONST               1 (1)
                            6 COMPARE_OP               4 (>)
                            9 POP_JUMP_IF_FALSE        20

                2           12 LOAD_CONST               0 (2)
                            15 PRINT_ITEM
                            16 PRINT_NEWLINE
                            17 JUMP_FORWARD             5 (to 25)

                4       >>  20 LOAD_CONST               1 (1)
                            23 PRINT_ITEM
                            24 PRINT_NEWLINE
            */
                v = POP();
                if (v == Universe::HiFalse) //如果上一步的比较操作为False，指令计数器pc移动至绝对位置20处，继续执行指令
                    _frame->set_pc(op_arg);
                break;

            case ByteCode::JUMP_FORWARD:
                _frame->set_pc(op_arg + _frame->get_pc());
                break;

            case ByteCode::JUMP_ABSOLUTE:
                _frame->set_pc(op_arg);
                break;
            
            case ByteCode::SETUP_LOOP:
                _frame->loop_stack()->append(new Block(op_code, _frame->get_pc()+op_arg, STACK_LEVEL()));
                break;

            case ByteCode::POP_BLOCK:
                b = _frame->loop_stack()->pop();
                while (STACK_LEVEL() > b->_level) {
                    POP();
                }
                break;
            
            case ByteCode::BREAK_LOOP:
                b = _frame->loop_stack()->pop();
                while (STACK_LEVEL() > b->_level) {
                    POP();
                }
                _frame->set_pc(b->_target);
                break;

            default:
                printf("Error: Unrecognized byte code %d\n", op_code);
        } 
    }
}