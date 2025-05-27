#include "br.h"

LIST_FUNCTION(_byte_set)
{
    Int index = BR_ARG(1).i;
    Int value = BR_ARG(2).i;

    (BR_ARG(0).s)[index] = value;
 
    return -1;
}

LIST_FUNCTION(_byte_get)
{
    Int byte_index = BR_ARG(1).i;
    Int index = br_new_var(context, NULL);
    BR_ARG(index).i = (BR_ARG(0).s)[byte_index];

    return index;
}

LIST_FUNCTION(_byte_add)
{
    Int index = BR_ARG(1).i;
    Int value = BR_ARG(2).i;

    BR_ARG(0).u8[index] += value;
 
    return -1;
}

LIST_FUNCTION(_byte_sub)
{
    Int index = BR_ARG(1).i;
    Int value = BR_ARG(2).i;

    BR_ARG(0).u8[index] -= value;
 
    return -1;
}

LIST_FUNCTION(_byte_mul)
{
    Int index = BR_ARG(1).i;
    Int value = BR_ARG(2).i;

    BR_ARG(0).u8[index] *= value;
 
    return -1;
}

LIST_FUNCTION(_byte_div)
{
    Int index = BR_ARG(1).i;
    Int value = BR_ARG(2).i;

    BR_ARG(0).u8[index] /= value;
 
    return -1;
}

BR_INIT(byte)
{
    br_add_function(context, "byte.set", _byte_set);
    br_add_function(context, "byte.get", _byte_get);
    
    br_add_function(context, "byte.add", _byte_add);
    br_add_function(context, "byte.sub", _byte_sub);
    br_add_function(context, "byte.mul", _byte_mul);
    br_add_function(context, "byte.div", _byte_div);
}
