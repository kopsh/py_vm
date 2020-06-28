# ifndef UNIVERSE_HPP
# define UNIVERSE_HPP

# include "object/HiInteger.hpp"

class Universe {
public:
    static HiString* HiFalse;
    static HiString* HiTrue;
    static HiObject* HiNone;

    static void genesis();
    static void destory();
};

# endif