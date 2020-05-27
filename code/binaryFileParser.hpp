# ifndef BINARY_FILE_PARSER
# define BINARY_FILE_PARSER

# include "util/BufferedInputStream.hpp"
# include "code/CodeObject.hpp"
# include "object/HiString.hpp"
# include "util/ArrayList.hpp"

class BinaryFileParser {
private:
    BufferedInputStream* file_stream;
    int cur;
    ArrayList<HiString*> _string_table;

public:
    BinaryFileParser(BufferedInputStream* stream);

    int get_int();

    CodeObject* parse();
    CodeObject* get_code_object();
    HiString* get_byte_codes();
    HiString* get_name();
    HiString* get_file_name();
    HiString* get_no_table();
    HiString* get_string();

    ArrayList<HiObject*>* get_consts();
    ArrayList<HiObject*>* get_names();
    ArrayList<HiObject*>* get_var_names();
    ArrayList<HiObject*>* get_free_vars();
    ArrayList<HiObject*>* get_cell_vars();
    ArrayList<HiObject*>* get_tuple();
};
# endif