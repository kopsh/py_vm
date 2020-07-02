# ifndef TABLE_HPP
# define TABLE_HPP

# include "object/HiInteger.hpp"
# include "object/HiList.hpp"
# include "object/HiString.hpp"

class StringTable {
private:
    static StringTable* instance;
    StringTable() {
        next_str = new HiString("next");
        mod_str = new HiString("__module__");
        init_str = new HiString("__init__");
        add_str = new HiString("__add__");
        len_str = new HiString("__len__");
        call_str = new HiString("__call__");
        getitem_str = new HiString("__getitem__");
        setitem_str = new HiString("__setitem__");
        getattr_str = new HiString("__getattr__");
        setattr_str = new HiString("__setattr__");
    };

public:
    static StringTable* get_instance();
    
    HiString* next_str;
    HiString* mod_str;
    HiString* init_str;
    HiString* add_str;
    HiString* len_str;
    HiString* call_str;
    HiString* getitem_str;
    HiString* setitem_str;
    HiString* getattr_str;
    HiString* setattr_str;
};

class IntegerTable {
private:
    static IntegerTable* instance;
    HiList* _list;
    IntegerTable(); 

public:
    static IntegerTable* get_instance();
    static HiInteger* get(int);
};

# endif