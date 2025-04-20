#include "buxu.h"

function(_byte_set)
{
    Int index = arg(1).i;
    Int value = arg(2).i;

    arg(0).u8[index] = value;
 
    return -1;
}

function(_byte_get)
{
    Int index = arg(1).i;

    return arg(0).u8[index];
}

function(_byte_add)
{
    Int index = arg(1).i;
    Int value = arg(2).i;

    arg(0).u8[index] += value;
 
    return -1;
}

function(_byte_sub)
{
    Int index = arg(1).i;
    Int value = arg(2).i;

    arg(0).u8[index] -= value;
 
    return -1;
}

function(_byte_mul)
{
    Int index = arg(1).i;
    Int value = arg(2).i;

    arg(0).u8[index] *= value;
 
    return -1;
}

function(_byte_div)
{
    Int index = arg(1).i;
    Int value = arg(2).i;

    arg(0).u8[index] /= value;
 
    return -1;
}

init(bytes)
{
    add_function(vm, "byte.set", _byte_set);
    add_function(vm, "byte.get", _byte_get);
    
    add_function(vm, "byte.add", _byte_add);
    add_function(vm, "byte.sub", _byte_sub);
    add_function(vm, "byte.mul", _byte_mul);
    add_function(vm, "byte.div", _byte_div);
}
