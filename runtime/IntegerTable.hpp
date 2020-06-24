# ifndef INTEGER_TABLE_HPP
# define INTEGER_TABLE_HPP

# include "object/HiInteger.hpp"
# include "object/HiList.hpp"

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