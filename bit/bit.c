#include "buxu.h"

function(_bit_and)
{
    arg(0).i &= arg(1).i;
    return -1;
}

function(_bit_or)
{
    arg(0).i |= arg(1).i;
    return -1;
}

function(_bit_xor)
{
    arg(0).i ^= arg(1).i;
    return -1;
}

function(_bit_not)
{
    arg(0).i = ~arg(0).i;
    return -1;
}

function(_bit_lshift)
{
    arg(0).i <<= arg(1).i;
    return -1;
}

function(_bit_rshift)
{
    arg(0).i >>= arg(1).i;
    return -1;
}

function(_bit_set)
{
    Int mask = 1 << arg(1).i;
    arg(0).i |= mask;
    return -1;
}

function(_bit_clear)
{
    Int mask = ~(1 << arg(1).i);
    arg(0).i &= mask;
    return -1;
}

function(_bit_get)
{
    Int mask = 1 << arg(1).i;
    return (arg(0).i & mask) != 0;
}

function(_bit_switch)
{
    Int mask = 1 << arg(1).i;
    arg(0).i ^= mask;
    return -1;
}

function(_bit_swap)
{
    Int mask = 1 << arg(1).i;
    Int mask2 = 1 << arg(2).i;
    Int temp = (arg(0).i & mask) >> arg(1).i;
    arg(0).i &= ~mask;
    arg(0).i |= (temp << arg(2).i);
    return -1;
}

init(bits)
{
    add_function(vm, "bit.and", _bit_and);
    add_function(vm, "bit.or", _bit_or);
    add_function(vm, "bit.xor", _bit_xor);
    add_function(vm, "bit.not", _bit_not);
    add_function(vm, "bit.lshift", _bit_lshift);
    add_function(vm, "bit.rshift", _bit_rshift);
    add_function(vm, "bit.set", _bit_set);
    add_function(vm, "bit.clear", _bit_clear);
    add_function(vm, "bit.get", _bit_get);
    add_function(vm, "bit.switch", _bit_switch);
    add_function(vm, "bit.swap", _bit_swap);
}
