# ifndef STRING_TABLE_HPP
# define STRING_TABLE_HPP

# include "object/HiString.hpp"

class StringTable {
private:
    static StringTable* instance;
    StringTable() {
        next_str = new HiString("next");
    };

public:
    static StringTable* get_instance() {
        if (instance == NULL) {
            instance = new StringTable();
        }
        return instance;
    }
    
    HiString* next_str;
};

# endif