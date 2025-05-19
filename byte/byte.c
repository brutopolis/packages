#include "br.h"

LIST_FUNCTION(_byte_set)
{
    Int index = ARG(1).i;
    Int value = ARG(2).i;

    (ARG_S(0))[index] = value;
 
    return -1;
}

LIST_FUNCTION(_byte_get)
{
    Int byte_index = ARG(1).i;
    Int index = new_var(context, NULL);
    ARG(index).i = (ARG_S(0))[byte_index];

    return index;
}

LIST_FUNCTION(_byte_add)
{
    Int index = ARG(1).i;
    Int value = ARG(2).i;

    ARG(0).u8[index] += value;
 
    return -1;
}

LIST_FUNCTION(_byte_sub)
{
    Int index = ARG(1).i;
    Int value = ARG(2).i;

    ARG(0).u8[index] -= value;
 
    return -1;
}

LIST_FUNCTION(_byte_mul)
{
    Int index = ARG(1).i;
    Int value = ARG(2).i;

    ARG(0).u8[index] *= value;
 
    return -1;
}

LIST_FUNCTION(_byte_div)
{
    Int index = ARG(1).i;
    Int value = ARG(2).i;

    ARG(0).u8[index] /= value;
 
    return -1;
}

INIT(byte)
{
    ADD_FUNCTION(context, "byte.set", _byte_set);
    ADD_FUNCTION(context, "byte.get", _byte_get);
    
    ADD_FUNCTION(context, "byte.add", _byte_add);
    ADD_FUNCTION(context, "byte.sub", _byte_sub);
    ADD_FUNCTION(context, "byte.mul", _byte_mul);
    ADD_FUNCTION(context, "byte.div", _byte_div);
}
