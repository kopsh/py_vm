# ifndef UNIVERSE_HPP
# define UNIVERSE_HPP

# include "object/HiInteger.hpp"

class Universe {
public:
    static HiInteger* HiFalse;
    static HiInteger* HiTrue;
    static HiObject* HiNone;

    static void genesis();
    static void destory();
};

# endif