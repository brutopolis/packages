#include "br.h"

LIST_FUNCTION(_bit_and)
{
    ARG(0).i &= ARG(1).i;
    return -1;
}

LIST_FUNCTION(_bit_or)
{
    ARG(0).i |= ARG(1).i;
    return -1;
}

LIST_FUNCTION(_bit_xor)
{
    ARG(0).i ^= ARG(1).i;
    return -1;
}

LIST_FUNCTION(_bit_not)
{
    ARG(0).i = ~ARG(0).i;
    return -1;
}

LIST_FUNCTION(_bit_lshift)
{
    ARG(0).i <<= ARG(1).i;
    return -1;
}

LIST_FUNCTION(_bit_rshift)
{
    ARG(0).i >>= ARG(1).i;
    return -1;
}

LIST_FUNCTION(_bit_on)
{
    Int mask = 1 << ARG(1).i;
    ARG(0).i |= mask;
    return -1;
}

LIST_FUNCTION(_bit_off)
{
    Int mask = ~(1 << ARG(1).i);
    ARG(0).i &= mask;
    return -1;
}

LIST_FUNCTION(_bit_set) // set 0 or 1
{
    Int mask = 1 << ARG(1).i;
    if (ARG(2).i)
        ARG(0).i |= mask;
    else
        ARG(0).i &= ~mask;
    return -1;
}


LIST_FUNCTION(_bit_get)
{
    Int mask = 1 << ARG(1).i;
    return (ARG(0).i & mask) != 0;
}

LIST_FUNCTION(_bit_switch)
{
    Int mask = 1 << ARG(1).i;
    ARG(0).i ^= mask;
    return -1;
}

LIST_FUNCTION(_bit_swap)
{
    Int mask = 1 << ARG(1).i;
    Int mask2 = 1 << ARG(2).i;
    Int temp = (ARG(0).i & mask) >> ARG(1).i;
    ARG(0).i &= ~mask;
    ARG(0).i |= (temp << ARG(2).i);
    return -1;
}

INIT(bit)
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
