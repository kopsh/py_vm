# ifndef _HI_STRING_HPP
# define _HI_STRING_HPP

# include "HiObject.hpp"
# include "util/ArrayList.hpp"

class StringKlass : public Klass {
private:
    StringKlass() {}
    static StringKlass* instance;

public:
    static StringKlass* get_instance();
    void initialize();
    virtual HiObject* allocate_instance(HiObject* callable, ObjList args);

    virtual void print(HiObject* obj);
    virtual void repr(HiObject* obj);
    virtual HiObject* equal(HiObject* x, HiObject* y);
    virtual HiObject* less(HiObject* x, HiObject* y);
    virtual HiObject* len(HiObject* x);
    virtual HiObject* subscr(HiObject* x, HiObject* y);
};

class HiString : public HiObject {
private:
    char * _value;
    int _length;

public:
    HiString(const char* x);
    HiString(const char* x, const int length);
    
    const char * value();
    int length();
};

HiObject* string_upper(ObjList args);

# endif