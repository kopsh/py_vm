class ByteCode {
public:
    static const unsigned char BINARY_ADD = 23;
    static const unsigned char PRINT_ITEM = 71;
    static const unsigned char PRINT_NEWLINE = 72;
    static const unsigned char RETURN_VALUE = 83;
    static const unsigned char HAVE_ARGUMENT = 90;

    /* index in const list */
    static const unsigned char LOAD_CONST = 100;

    /* compare operator */
    static const unsigned char COMPARE_OF = 107;

    /* number of bytes to skip */
    static const unsigned char JUMP_FORWARD = 110;
    static const unsigned char POP_JUMP_IF_FALSE = 114;

    enum COMPARE {
        LESS = 0,
        LESS_EQUAL,
        EQUAL,
        NOT_EQUAL,
        GREATER,
        EQUALER_GREATER
    }
};