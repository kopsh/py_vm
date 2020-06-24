# include "runtime/IntegerTable.hpp"

class HiInteger;

IntegerTable::IntegerTable() {
    _list = new HiList();

    for (int i=0; i < 10; i++) {
        _list->append(new HiInteger(i));
    }
};

IntegerTable* IntegerTable::instance = NULL;

IntegerTable* IntegerTable::get_instance() {
    if (instance == NULL) {
        instance = new IntegerTable();
    }
    return instance;
}

HiInteger* IntegerTable::get(int i) {
    if (instance == NULL) {
        instance = new IntegerTable();
    }
    if (i >=0 && i < 10){
        return (HiInteger*) (instance->_list->get(i));
    }
    return new HiInteger(i);
}   