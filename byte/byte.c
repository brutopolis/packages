#include <bruter-representation.h>

BR_FUNCTION(_byte_set)
{
    BruterInt index = br_arg_get(context, args, 1).i;
    BruterInt value = br_arg_get(context, args, 2).i;

    (br_arg_get(context, args, 0).s)[index] = value;
 
    return -1;
}

BR_FUNCTION(_byte_get)
{
    BruterInt byte_index = br_arg_get(context, args, 1).i;
    BruterInt index = br_new_var(context, bruter_value_i(bruter_get(context, index).u8[byte_index]), NULL, BR_TYPE_ANY);
    return index;
}

BR_FUNCTION(_byte_add)
{
    BruterInt index = br_arg_get(context, args, 1).i;
    BruterInt value = br_arg_get(context, args, 2).i;

    br_arg_get(context, args, 0).u8[index] += value;
 
    return -1;
}

BR_FUNCTION(_byte_sub)
{
    BruterInt index = br_arg_get(context, args, 1).i;
    BruterInt value = br_arg_get(context, args, 2).i;

    br_arg_get(context, args, 0).u8[index] -= value;
 
    return -1;
}

BR_FUNCTION(_byte_mul)
{
    BruterInt index = br_arg_get(context, args, 1).i;
    BruterInt value = br_arg_get(context, args, 2).i;

    br_arg_get(context, args, 0).u8[index] *= value;
 
    return -1;
}

BR_FUNCTION(_byte_div)
{
    BruterInt index = br_arg_get(context, args, 1).i;
    BruterInt value = br_arg_get(context, args, 2).i;

    br_arg_get(context, args, 0).u8[index] /= value;
 
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
