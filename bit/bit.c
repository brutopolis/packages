#include "buxu.h"

list_function(_bit_and)
{
    arg(0).i &= arg(1).i;
    return -1;
}

list_function(_bit_or)
{
    arg(0).i |= arg(1).i;
    return -1;
}

list_function(_bit_xor)
{
    arg(0).i ^= arg(1).i;
    return -1;
}

list_function(_bit_not)
{
    arg(0).i = ~arg(0).i;
    return -1;
}

list_function(_bit_lshift)
{
    arg(0).i <<= arg(1).i;
    return -1;
}

list_function(_bit_rshift)
{
    arg(0).i >>= arg(1).i;
    return -1;
}

list_function(_bit_on)
{
    Int mask = 1 << arg(1).i;
    arg(0).i |= mask;
    return -1;
}

list_function(_bit_off)
{
    Int mask = ~(1 << arg(1).i);
    arg(0).i &= mask;
    return -1;
}

list_function(_bit_set) // set 0 or 1
{
    Int mask = 1 << arg(1).i;
    if (arg(2).i)
        arg(0).i |= mask;
    else
        arg(0).i &= ~mask;
    return -1;
}


list_function(_bit_get)
{
    Int mask = 1 << arg(1).i;
    return (arg(0).i & mask) != 0;
}

list_function(_bit_switch)
{
    Int mask = 1 << arg(1).i;
    arg(0).i ^= mask;
    return -1;
}

list_function(_bit_swap)
{
    Int mask = 1 << arg(1).i;
    Int mask2 = 1 << arg(2).i;
    Int temp = (arg(0).i & mask) >> arg(1).i;
    arg(0).i &= ~mask;
    arg(0).i |= (temp << arg(2).i);
    return -1;
}

init(bit)
{
    add_function(context, "bit.and", _bit_and);
    add_function(context, "bit.or", _bit_or);
    add_function(context, "bit.xor", _bit_xor);
    add_function(context, "bit.not", _bit_not);
    add_function(context, "bit.lshift", _bit_lshift);
    add_function(context, "bit.rshift", _bit_rshift);
    add_function(context, "bit.on", _bit_on);
    add_function(context, "bit.off", _bit_off);
    add_function(context, "bit.set", _bit_set);
    add_function(context, "bit.get", _bit_get);
    add_function(context, "bit.switch", _bit_switch);
    add_function(context, "bit.swap", _bit_swap);
}
