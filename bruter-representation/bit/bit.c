#include <bruter-representation.h>

BR_FUNCTION(_bit_and)
{
    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i & br_arg_get(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_bit_or)
{
    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i | br_arg_get(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_bit_xor)
{
    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i ^ br_arg_get(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_bit_not)
{
    br_arg_set(context, args, 0, bruter_value_int(~br_arg_get(context, args, 0).i));
    return -1;
}

BR_FUNCTION(_bit_lshift)
{
    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i << br_arg_get(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_bit_rshift)
{
    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i >> br_arg_get(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_bit_on)
{
    BruterInt mask = 1 << br_arg_get(context, args, 1).i;
    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i | mask));
    return -1;
}

BR_FUNCTION(_bit_off)
{
    BruterInt mask = 1 << br_arg_get(context, args, 1).i;
    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i & ~mask));
    return -1;
}

BR_FUNCTION(_bit_set) // set 0 or 1
{
    BruterInt mask = 1 << br_arg_get(context, args, 1).i;
    if (br_arg_get(context, args, 2).i)
        br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i | mask));
    else
        br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i & ~mask));
    return -1;
}

BR_FUNCTION(_bit_get)
{
    BruterInt mask = 1 << br_arg_get(context, args, 1).i;
    return (br_arg_get(context, args, 0).i & mask) ? 1 : 0;
}

BR_FUNCTION(_bit_switch)
{
    BruterInt mask = 1 << br_arg_get(context, args, 1).i;
    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i ^ mask));
    return -1;
}

BR_FUNCTION(_bit_swap)
{
    BruterInt mask = 1 << br_arg_get(context, args, 1).i;
    BruterInt mask2 = 1 << br_arg_get(context, args, 2).i;
    BruterInt temp = (br_arg_get(context, args, 0).i & mask) >> br_arg_get(context, args, 1).i;
    temp ^= (br_arg_get(context, args, 0).i & mask2) >> br_arg_get(context, args, 2).i;
    temp &= 1; // ensure it's only 0 or 1
    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i & ~(mask | mask2)));
    return -1;
}

BR_INIT(bit)
{
    bruter_push_pointer(context, _bit_and, "bit.and", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, _bit_or, "bit.or", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, _bit_xor, "bit.xor", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, _bit_not, "bit.not", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, _bit_lshift, "bit.lshift", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, _bit_rshift, "bit.rshift", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, _bit_on, "bit.on", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, _bit_off, "bit.off", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, _bit_set, "bit.set", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, _bit_get, "bit.get", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, _bit_switch, "bit.switch", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, _bit_swap, "bit.swap", BR_TYPE_FUNCTION);
}
