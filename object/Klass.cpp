# include "object/Klass.hpp"
# include "object/HiInteger.hpp"
# include "object/HiString.hpp"
# include "runtime/universe.hpp"

int Klass::compare_klass(Klass* x, Klass* y) {
    if (x == y)
        return 0;

    if (x == IntegerKlass::get_instance())
        return -1;
    else if (y == IntegerKlass::get_instance())
        return 1;
    
    if (x->name()->less(y->name()) == Universe::HiTrue)
        return -1;
    else
        return 1;
}