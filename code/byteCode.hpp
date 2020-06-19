class ByteCode {
public:
    static const unsigned char POP_TOP = 1;
    static const unsigned char POP_TWO = 2;
    static const unsigned char BINARY_ADD = 23;
    static const unsigned char BINARY_SUBSCR = 25;
    static const unsigned char STORE_SUBSCR = 60;
    static const unsigned char DELETE_SUBSCR = 61;

    static const unsigned char PRINT_ITEM = 71;
    static const unsigned char PRINT_NEWLINE = 72;

    static const unsigned char BREAK_LOOP = 80;
    static const unsigned char RETURN_VALUE = 83;
    static const unsigned char POP_BLOCK = 87;

    // Opcodes from here have an argument
    static const unsigned char HAVE_ARGUMENT = 90; 

    static const unsigned char STORE_NAME = 90; // Index in name list
    static const unsigned char LOAD_CONST = 100; // index in const list
    static const unsigned char LOAD_NAME = 101; // index in name list

    static const unsigned char BUILD_LIST= 103; // index in name list
    static const unsigned char BUILD_MAP = 105; // index in name list

    static const unsigned char LOAD_ATTR = 106; // index in name list
    static const unsigned char COMPARE_OF = 107; // compare operator

    static const unsigned char JUMP_FORWARD = 110; // number of bytes to skip
    static const unsigned char JUMP_ABSOLUTE = 113;
    static const unsigned char POP_JUMP_IF_FALSE = 114;
    static const unsigned char LOAD_GLOBAL = 116; // index in name list

    static const unsigned char SETUP_LOOP = 120; // target address (relative)

    static const unsigned char LOAD_FAST  = 124; /* Local variable number */
    static const unsigned char STORE_FAST = 125; /* Local variable number */

    static const unsigned char CALL_FUNCTION = 131;
    static const unsigned char MAKE_FUNCTION = 132;

    enum COMPARE {
        LESS = 0,
        LESS_EQUAL,
        EQUAL,
        NOT_EQUAL,
        GREATER,
        GREATER_EQUAL,
        IN,
        NOT_IN,
        IS,
        IS_NOT
    };
};