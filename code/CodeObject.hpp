# ifndef CODE_OBJECT_HPP
# define CODE_OBJECT_HPP

# include "object/HiObject.hpp"

class HiString;

template <typename T>
class ArrayList;

class CodeObject : public HiObject {
public:
    int _argcount;
    int _nlocals;
    int _stacksize;
    int _flag;

    HiString* _bytecodes;
    ArrayList<HiObject*>* _names;
    ArrayList<HiObject*>* _consts;
    ArrayList<HiObject*>* _var_names;

    ArrayList<HiObject*>* _free_vals;
    ArrayList<HiObject*>* _cell_vals;

    HiString* _co_name; // code object name
    HiString* _file_name;

    int _lineno;
    HiString* _notable;

    CodeObject(int argcount, int nlocals, int stacksize, int flag, HiString* bytecodes,
               ArrayList<HiObject*>* consts, ArrayList<HiObject*>* names, 
               ArrayList<HiObject*>* var_names, ArrayList<HiObject*>* free_vals,
               ArrayList<HiObject*>* cell_vals, HiString* co_name, HiString* file_name,
               int lineno, HiString* notable);
  
};

# endif