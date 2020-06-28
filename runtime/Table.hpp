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
    };

public:
    static StringTable* get_instance();
    
    HiString* next_str;
    HiString* mod_str;
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