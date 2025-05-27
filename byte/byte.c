#include "br.h"

BRUTER_FUNCTION(_byte_set)
{
    BruterInt index = BR_ARG(1).i;
    BruterInt value = BR_ARG(2).i;

    (BR_ARG(0).s)[index] = value;
 
    return -1;
}

BRUTER_FUNCTION(_byte_get)
{
    BruterInt byte_index = BR_ARG(1).i;
    BruterInt index = br_new_var(context, NULL);
    BR_ARG(index).i = (BR_ARG(0).s)[byte_index];

    return index;
}

BRUTER_FUNCTION(_byte_add)
{
    BruterInt index = BR_ARG(1).i;
    BruterInt value = BR_ARG(2).i;

    BR_ARG(0).u8[index] += value;
 
    return -1;
}

BRUTER_FUNCTION(_byte_sub)
{
    BruterInt index = BR_ARG(1).i;
    BruterInt value = BR_ARG(2).i;

    BR_ARG(0).u8[index] -= value;
 
    return -1;
}

BRUTER_FUNCTION(_byte_mul)
{
    BruterInt index = BR_ARG(1).i;
    BruterInt value = BR_ARG(2).i;

    BR_ARG(0).u8[index] *= value;
 
    return -1;
}

BRUTER_FUNCTION(_byte_div)
{
    BruterInt index = BR_ARG(1).i;
    BruterInt value = BR_ARG(2).i;

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
