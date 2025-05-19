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
    ADD_FUNCTION(context, "bit.and", _bit_and);
    ADD_FUNCTION(context, "bit.or", _bit_or);
    ADD_FUNCTION(context, "bit.xor", _bit_xor);
    ADD_FUNCTION(context, "bit.not", _bit_not);
    ADD_FUNCTION(context, "bit.lshift", _bit_lshift);
    ADD_FUNCTION(context, "bit.rshift", _bit_rshift);
    ADD_FUNCTION(context, "bit.on", _bit_on);
    ADD_FUNCTION(context, "bit.off", _bit_off);
    ADD_FUNCTION(context, "bit.set", _bit_set);
    ADD_FUNCTION(context, "bit.get", _bit_get);
    ADD_FUNCTION(context, "bit.switch", _bit_switch);
    ADD_FUNCTION(context, "bit.swap", _bit_swap);
}
