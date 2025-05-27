#include "br.h"

LIST_FUNCTION(_bit_and)
{
    BR_ARG(0).i &= BR_ARG(1).i;
    return -1;
}

LIST_FUNCTION(_bit_or)
{
    BR_ARG(0).i |= BR_ARG(1).i;
    return -1;
}

LIST_FUNCTION(_bit_xor)
{
    BR_ARG(0).i ^= BR_ARG(1).i;
    return -1;
}

LIST_FUNCTION(_bit_not)
{
    BR_ARG(0).i = ~BR_ARG(0).i;
    return -1;
}

LIST_FUNCTION(_bit_lshift)
{
    BR_ARG(0).i <<= BR_ARG(1).i;
    return -1;
}

LIST_FUNCTION(_bit_rshift)
{
    BR_ARG(0).i >>= BR_ARG(1).i;
    return -1;
}

LIST_FUNCTION(_bit_on)
{
    Int mask = 1 << BR_ARG(1).i;
    BR_ARG(0).i |= mask;
    return -1;
}

LIST_FUNCTION(_bit_off)
{
    Int mask = ~(1 << BR_ARG(1).i);
    BR_ARG(0).i &= mask;
    return -1;
}

LIST_FUNCTION(_bit_set) // set 0 or 1
{
    Int mask = 1 << BR_ARG(1).i;
    if (BR_ARG(2).i)
        BR_ARG(0).i |= mask;
    else
        BR_ARG(0).i &= ~mask;
    return -1;
}


LIST_FUNCTION(_bit_get)
{
    Int mask = 1 << BR_ARG(1).i;
    return (BR_ARG(0).i & mask) != 0;
}

LIST_FUNCTION(_bit_switch)
{
    Int mask = 1 << BR_ARG(1).i;
    BR_ARG(0).i ^= mask;
    return -1;
}

LIST_FUNCTION(_bit_swap)
{
    Int mask = 1 << BR_ARG(1).i;
    Int mask2 = 1 << BR_ARG(2).i;
    Int temp = (BR_ARG(0).i & mask) >> BR_ARG(1).i;
    BR_ARG(0).i &= ~mask;
    BR_ARG(0).i |= (temp << BR_ARG(2).i);
    return -1;
}

BR_INIT(bit)
{
    br_add_function(context, "bit.and", _bit_and);
    br_add_function(context, "bit.or", _bit_or);
    br_add_function(context, "bit.xor", _bit_xor);
    br_add_function(context, "bit.not", _bit_not);
    br_add_function(context, "bit.lshift", _bit_lshift);
    br_add_function(context, "bit.rshift", _bit_rshift);
    br_add_function(context, "bit.on", _bit_on);
    br_add_function(context, "bit.off", _bit_off);
    br_add_function(context, "bit.set", _bit_set);
    br_add_function(context, "bit.get", _bit_get);
    br_add_function(context, "bit.switch", _bit_switch);
    br_add_function(context, "bit.swap", _bit_swap);
}
