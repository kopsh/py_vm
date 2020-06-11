# ifndef _HI_STRING_HPP
# define _HI_STRING_HPP

# include "HiObject.hpp"

class StringKlass : public Klass {
private:
    StringKlass() {}
    static StringKlass* instance;

public:
    static StringKlass* get_instance();

    virtual void print(HiObject* obj);
    virtual HiObject* equal(HiObject* x, HiObject* y);
    virtual HiObject* len(HiObject* x);
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


# endif