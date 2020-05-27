# include "CodeObject.hpp"

CodeObject::CodeObject(int argcount, int nlocals, int stacksize, int flag, HiString* bytecodes,
               ArrayList<HiObject*>* consts, ArrayList<HiObject*>* names, 
               ArrayList<HiObject*>* var_names, ArrayList<HiObject*>* free_vals,
               ArrayList<HiObject*>* cell_vals, HiString* co_name, HiString* file_name,
               int lineno, HiString* notable):
               _argcount(argcount),
               _nlocals(nlocals),
               _stacksize(stacksize),
               _flag(flag),
               _bytecodes(bytecodes),
               _consts(consts),
               _names(names),
               _var_names(var_names),
               _free_vals(free_vals),
               _cell_vals(cell_vals),
               _co_name(co_name),
               _file_name(file_name),
               _lineno(lineno),
               _notable(notable) {
}