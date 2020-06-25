# include "code/CodeObject.hpp"
# include "object/HiDict.hpp"
# include "object/HiInteger.hpp"
# include "object/HiList.hpp"
# include "object/HiString.hpp"
# include "runtime/cellObject.hpp"
# include "runtime/IntegerTable.hpp"
# include "runtime/StringTable.hpp"
# include "runtime/functionObject.hpp"
# include "runtime/interpreter.hpp"
# include "runtime/universe.hpp"
# include "util/ArrayList.hpp"
# include "util/Map.hpp"

# include <string.h>
# include <iostream>

# define PUSH(x) _frame->stack()->append((x))
# define POP() _frame->stack()->pop()
# define TOP() _frame->stack()->top()
# define STACK_LEVEL() _frame->stack()->size()

# define HI_TRUE Universe::HiTrue
# define HI_FALSE Universe::HiFalse
# define HI_NONE Universe::HiNone

Interpreter* Interpreter::_instance = NULL;

Interpreter* Interpreter::get_instance() {
    if (_instance == NULL) {
        _instance = new Interpreter();
    }

    return _instance;
}

Interpreter::Interpreter() {
    _frame = NULL;

    _builtins = new HiDict();

    _builtins->put(new HiString("True"), HI_TRUE);
    _builtins->put(new HiString("False"), HI_FALSE);
    _builtins->put(new HiString("None"), HI_NONE);

    _builtins->put(new HiString("len"), new FunctionObject(len));
}

// 创建新的frameObject，由它维护新的运行状态
void Interpreter::build_frame(HiObject* callable, ObjList args, int op_arg) {
    if (callable->klass() == NativeFunctionKlass::get_instance()) {
        PUSH(((FunctionObject* )callable)->call(args));
    }
    else if (callable->klass() == FunctionKlass::get_instance()) {
        FrameObject* frame = new FrameObject((FunctionObject* ) callable, args, op_arg);
        frame->set_sender(_frame);
        _frame = frame;
    }
    else if (callable->klass() == MethodKlass::get_instance()) {
        MethodObject* mo = (MethodObject* ) callable;
        if (args == NULL)
            args = new ArrayList<HiObject*>(1);
        args->insert(0, mo->owner());
        build_frame(mo->func(), args, op_arg + 1);
    }
}

void Interpreter::run(CodeObject* codes) {
    _frame = new FrameObject(codes);
    eval_frame();
    destory_frame();
}

void Interpreter::destory_frame() {
    if (_frame->is_first_frame())
        return;

    FrameObject* temp = _frame;
    _frame = _frame->sender();

    delete temp;
}

// void Interpreter::leave_frame() {
// 
// }

void Interpreter::eval_frame() {
    Block* b;
    int op_arg;
    unsigned char op_code;
    bool has_argument;
    ArrayList<HiObject*>* args = NULL;

    FunctionObject* fo;

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
            case ByteCode::POP_TOP:
                POP();
                break;

            case ByteCode::LOAD_CONST:
                PUSH(_frame->consts()->get(op_arg));
                break;

            case ByteCode::STORE_NAME:
                v = _frame->names()->get(op_arg);
                _frame->locals()->put(v, POP());
                break;
            
            case ByteCode::LOAD_NAME:
                v = _frame->names()->get(op_arg);
                w = _frame->locals()->get(v);
                if (w != HI_NONE) {
                    PUSH(w);
                    break;
                }
                w = _frame->globals()->get(v);
                if (w != HI_NONE) {
                    PUSH(w);
                    break;
                }
                w = _builtins->get(v);
                if (w != HI_NONE) {
                    PUSH(w);
                    break;
                }
                PUSH(HI_NONE);
                break;

            case ByteCode::LOAD_GLOBAL:
                v = _frame->names()->get(op_arg);
                w = _frame->globals()->get(v);
                if (w != HI_NONE) {
                    PUSH(w);
                    break;
                }
                w = _builtins->get(v);
                if (w != HI_NONE) {
                    PUSH(w);
                    break;
                }
                PUSH(HI_NONE);
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
            
            case ByteCode::BINARY_SUBSCR:
                v = POP();
                w = POP();
                PUSH(w->subscr(v));
                break;

            case ByteCode::STORE_SUBSCR:
                u = POP();
                v = POP();
                w = POP();
                v->store_subscr(u, w);
                break;

            case ByteCode::DELETE_SUBSCR:
                v = POP();
                w = POP();
                w->delete_subscr(v);
                break;

            case ByteCode::RETURN_VALUE:
                _ret_value = POP();
                // leave_frame();
                destory_frame();
                PUSH(_ret_value);
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

                    case ByteCode::IN:
                        PUSH(w->contains(v));
                        break;

                    case ByteCode::NOT_IN:
                        PUSH(w->contains_not(v));
                        break;

                    case ByteCode::IS:
                        if (v == w)
                            PUSH(HI_TRUE);
                        else
                            PUSH(HI_FALSE);
                        break;

                    case ByteCode::IS_NOT:
                        if (v == w)
                            PUSH(HI_FALSE);
                        else
                            PUSH(HI_TRUE);
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
                if (v == HI_FALSE) //如果上一步的比较操作为False，指令计数器pc移动至绝对位置20处，继续执行指令
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

            case ByteCode::MAKE_FUNCTION:
                v = POP();
                fo = new FunctionObject(v);
                fo->set_globals(_frame->globals());
                if (op_arg > 0) {
                    args = new ArrayList<HiObject*>(op_arg);

                    while (op_arg--) {
                        args->set(op_arg, POP());
                    }

                    fo->set_defaults(args);

                    if (args != NULL) {
                        delete args;
                        args = NULL;
                    }
                }

                PUSH(fo);
                break;

            case ByteCode::CALL_FUNCTION: 
            /*
                切换为新的frameObject，新的frameObject的sender指针指向调用它的frameObject
                CALL_FUNCTION的op_arg代表参数个数，其中高8位代表键参数的个数，低8位代表位置参数的个数
            */ 
                if (op_arg > 0) {
                    int na = op_arg & 0xff; // 低8位代表位置参数的个数
                    int nk = op_arg >> 8; // 高8位代表键参数的个数
                    int arg_cnt = na + nk * 2;
                    args = new ArrayList<HiObject*>(arg_cnt);
                    while (arg_cnt--) {
                        args->set(arg_cnt, POP());
                    }
                }

                build_frame(POP(), args, op_arg);

                if (args != NULL) {
                    delete args;
                    args = NULL;
                }
                break;

            case ByteCode::LOAD_FAST:
                PUSH(_frame->_fast_locals->get(op_arg));
                break;

            case ByteCode::STORE_FAST:
                _frame->_fast_locals->set(op_arg, POP());
                break;

            case ByteCode::LOAD_ATTR:
                v = POP();
                w = _frame->names()->get(op_arg);
                PUSH(v->getattr(w));
                break;

            case ByteCode::BUILD_TUPLE:
            case ByteCode::BUILD_LIST:
                v = new HiList();
                while (op_arg--) {
                    ((HiList*) v)->set(op_arg, POP());
                }
                PUSH(v);
                break;

            case ByteCode::GET_ITER:
                v = POP();
                PUSH(v->iter());
                break;

            case ByteCode::FOR_ITER:
                v = TOP();
                PUSH(v->next());

                if (TOP() == NULL) {
                    _frame->_pc += op_arg;
                    POP();
                }
                break;

            case ByteCode::BUILD_MAP:
                v = new HiDict();
                PUSH(v);
                break;

            case ByteCode::STORE_MAP:
                w = POP();
                v = POP();
                u = TOP();
                ((HiDict*) u)->put(w, v);
                break;

            case ByteCode::UNPACK_SEQUENCE:
                v = POP();

                while (op_arg--) {
                    PUSH(v->subscr(IntegerTable::get(op_arg)));
                }
                break;

            case ByteCode::STORE_DEREF:
                _frame->_closure->set(op_arg, POP());
                break;
            
            case ByteCode::LOAD_DEREF:
                v = _frame->closure()->get(op_arg);
                if (v->klass() == CellKlass::get_instance()) {
                    v = ((CellObject*)v)->value();
                }
                PUSH(v);
                break;

            case ByteCode::LOAD_CLOSURE:
                v = _frame->closure()->get(op_arg);
                if (v != NULL) {
                    PUSH(v);
                    break;
                }
                PUSH(_frame->get_cell_from_parameter(op_arg));
                break;

            case ByteCode::MAKE_CLOSURE:
                v = POP();
                fo = new FunctionObject(v);
                fo->set_closure((HiList*)(POP()));
                fo->set_globals(_frame->globals());

                if (op_arg > 0) {
                    args = new ArrayList<HiObject*>(op_arg);
                    while (op_arg--)
                        args->set(op_arg, POP());
                }
                fo->set_defaults(args);

                if (args != NULL)
                    args = NULL;

                PUSH(fo);
                break;

            default:
                printf("Error: Unrecognized byte code %d\n", op_code);
        } 
    }
}