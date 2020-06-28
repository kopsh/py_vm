# ifndef UNIVERSE_HPP
# define UNIVERSE_HPP

# include "object/HiInteger.hpp"

class Universe {
public:
    static HiObject* HiFalse;
    static HiObject* HiTrue;
    static HiObject* HiNone;

    static void genesis();
    static void destory();
};

# endif