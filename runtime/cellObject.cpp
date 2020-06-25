# include "runtime/cellObject.hpp"

CellKlass* CellKlass::instance = NULL;

CellKlass::CellKlass() {
    
}

CellKlass* CellKlass::get_instance() {
    if (instance == NULL) {
        instance = new CellKlass();
    }
    return instance;
}

