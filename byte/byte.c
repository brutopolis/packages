#include "buxu.h"

list_function(_byte_set)
{
    Int index = arg(1).i;
    Int value = arg(2).i;

    (arg_s(0))[index] = value;
 
    return -1;
}

list_function(_byte_get)
{
    Int byte_index = arg(1).i;
    Int index = new_var(context, NULL);
    arg(index).i = (arg_s(0))[byte_index];

    return index;
}

list_function(_byte_add)
{
    Int index = arg(1).i;
    Int value = arg(2).i;

    arg(0).u8[index] += value;
 
    return -1;
}

list_function(_byte_sub)
{
    Int index = arg(1).i;
    Int value = arg(2).i;

    arg(0).u8[index] -= value;
 
    return -1;
}

list_function(_byte_mul)
{
    Int index = arg(1).i;
    Int value = arg(2).i;

    arg(0).u8[index] *= value;
 
    return -1;
}

list_function(_byte_div)
{
    Int index = arg(1).i;
    Int value = arg(2).i;

    arg(0).u8[index] /= value;
 
    return -1;
}

init(byte)
{
    add_function(context, "byte.set", _byte_set);
    add_function(context, "byte.get", _byte_get);
    
    add_function(context, "byte.add", _byte_add);
    add_function(context, "byte.sub", _byte_sub);
    add_function(context, "byte.mul", _byte_mul);
    add_function(context, "byte.div", _byte_div);
}
