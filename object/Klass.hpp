# ifndef KLASS_HPP
# define KLASS_HPP

class HiObject;
class HiString;

class Klass {
private:
    HiString* _name;

public:
    Klass() {};
    void set_name(HiString* x) {_name = x;}
    HiString* name() {return _name;}

    virtual void print(HiObject* obj) {};
    virtual HiObject* greater(HiObject* x, HiObject* y) {return 0;}
    virtual HiObject* less(HiObject* x, HiObject* y) {return 0;}
    virtual HiObject* equal(HiObject* x, HiObject* y) {return 0;}
    virtual HiObject* not_equal(HiObject* x, HiObject* y) {return 0;}
    virtual HiObject* ge(HiObject* x, HiObject* y) {return 0;}
    virtual HiObject* le(HiObject* x, HiObject* y) {return 0;}

    virtual HiObject* add(HiObject* x, HiObject* y) {return 0;}
    virtual HiObject* sub(HiObject* x, HiObject* y) {return 0;}
    virtual HiObject* mul(HiObject* x, HiObject* y) {return 0;}
    virtual HiObject* div(HiObject* x, HiObject* y) {return 0;}
    virtual HiObject* mod(HiObject* x, HiObject* y) {return 0;}
};

# endif