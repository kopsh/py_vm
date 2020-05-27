# ifndef _HI_STRING_HPP
# define _HI_STRING_HPP


# include "HiObject.hpp"

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