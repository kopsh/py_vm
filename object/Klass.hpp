# ifndef KLASS_HPP
# define KLASS_HPP

class HiObject;
class HiString;
class HiDict;

class Klass {
private:
    HiString* _name;
    HiDict* _klass_dict;

public:
    Klass() {};
    void set_name(HiString* x) {_name = x;}
    HiString* name() {return _name;}
    void set_klass_dict(HiDict* dict) {_klass_dict = dict;}
    HiDict* klass_dict() {return _klass_dict;}
    static int compare_klass(Klass* x, Klass* y);

    virtual void print(HiObject* obj) {}
    virtual void repr(HiObject* obj) {}
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

    virtual HiObject* len(HiObject* x) {return 0;}
    virtual HiObject* subscr(HiObject* x, HiObject* y) {return 0;}
    virtual void store_subscr(HiObject* x, HiObject* y, HiObject* z) {return;}
    virtual void delete_subscr(HiObject* x, HiObject* y) {return;}
    virtual HiObject* contains(HiObject* x, HiObject* y) {return 0;}
    virtual HiObject* contains_not(HiObject* x, HiObject* y) {return 0;}

    virtual HiObject* iter(HiObject* x) {return 0;}
    virtual HiObject* next(HiObject* x) {return 0;}
};

# endif