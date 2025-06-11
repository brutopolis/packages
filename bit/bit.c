#include "bruter-representation.h"

BR_FUNCTION(_bit_and)
{
    br_arg_set(context, args, 0, bruter_value_i(br_arg(context, args, 0).i & br_arg(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_bit_or)
{
    br_arg_set(context, args, 0, bruter_value_i(br_arg(context, args, 0).i | br_arg(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_bit_xor)
{
    br_arg_set(context, args, 0, bruter_value_i(br_arg(context, args, 0).i ^ br_arg(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_bit_not)
{
    br_arg_set(context, args, 0, bruter_value_i(~br_arg(context, args, 0).i));
    return -1;
}

BR_FUNCTION(_bit_lshift)
{
    br_arg_set(context, args, 0, bruter_value_i(br_arg(context, args, 0).i << br_arg(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_bit_rshift)
{
    br_arg_set(context, args, 0, bruter_value_i(br_arg(context, args, 0).i >> br_arg(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_bit_on)
{
    BruterInt mask = 1 << br_arg(context, args, 1).i;
    br_arg_set(context, args, 0, bruter_value_i(br_arg(context, args, 0).i | mask));
    return -1;
}

BR_FUNCTION(_bit_off)
{
    BruterInt mask = 1 << br_arg(context, args, 1).i;
    br_arg_set(context, args, 0, bruter_value_i(br_arg(context, args, 0).i & ~mask));
    return -1;
}

BR_FUNCTION(_bit_set) // set 0 or 1
{
    BruterInt mask = 1 << br_arg(context, args, 1).i;
    if (br_arg(context, args, 2).i)
        br_arg_set(context, args, 0, bruter_value_i(br_arg(context, args, 0).i | mask));
    else
        br_arg_set(context, args, 0, bruter_value_i(br_arg(context, args, 0).i & ~mask));
    return -1;
}

BR_FUNCTION(_bit_get)
{
    BruterInt mask = 1 << br_arg(context, args, 1).i;
    return (br_arg(context, args, 0).i & mask) ? 1 : 0;
}

BR_FUNCTION(_bit_switch)
{
    BruterInt mask = 1 << br_arg(context, args, 1).i;
    br_arg_set(context, args, 0, bruter_value_i(br_arg(context, args, 0).i ^ mask));
    return -1;
}

BR_FUNCTION(_bit_swap)
{
    BruterInt mask = 1 << br_arg(context, args, 1).i;
    BruterInt mask2 = 1 << br_arg(context, args, 2).i;
    BruterInt temp = (br_arg(context, args, 0).i & mask) >> br_arg(context, args, 1).i;
    temp ^= (br_arg(context, args, 0).i & mask2) >> br_arg(context, args, 2).i;
    temp &= 1; // ensure it's only 0 or 1
    br_arg_set(context, args, 0, bruter_value_i(br_arg(context, args, 0).i & ~(mask | mask2)));
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
