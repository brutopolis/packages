#include <bruter-representation.h>

BR_FUNCTION(_byte_set)
{
    BruterInt index = br_arg_get(context, args, 1).i;
    BruterInt value = br_arg_get(context, args, 2).i;

    memset((br_arg_get(context, args, 0).p) + index, value, 1);
 
    return -1;
}

BR_FUNCTION(_byte_get)
{
    BruterInt byte_index = br_arg_get(context, args, 1).i;
    uint8_t *byte_ptr = br_arg_get(context, args, 0).p;
    if (byte_index < 0 || byte_index >= sizeof(uint8_t))
    {        printf("BR_ERROR: byte index out of range in byte.get\n");
        return -1; // or handle error as needed
    }
    BruterInt index = br_new_var(context, bruter_value_int(byte_ptr[byte_index]), NULL, BR_TYPE_ANY);
    return index;
}

BR_FUNCTION(_byte_add)
{
    BruterInt index = br_arg_get(context, args, 1).i;
    BruterInt value = br_arg_get(context, args, 2).i;
    uint8_t *byte_ptr = br_arg_get(context, args, 0).p;
    byte_ptr[index] = byte_ptr[index] + value; // addition by value
    return -1;
}

BR_FUNCTION(_byte_sub)
{
    BruterInt index = br_arg_get(context, args, 1).i;
    BruterInt value = br_arg_get(context, args, 2).i;
    uint8_t *byte_ptr = br_arg_get(context, args, 0).p;
    byte_ptr[index] = byte_ptr[index] - value; // subtraction by value
    return -1;
}

BR_FUNCTION(_byte_mul)
{
    BruterInt index = br_arg_get(context, args, 1).i;
    BruterInt value = br_arg_get(context, args, 2).i;
    uint8_t *byte_ptr = br_arg_get(context, args, 0).p;
    byte_ptr[index] = byte_ptr[index] * value; // multiplication by value
    return -1;
}

BR_FUNCTION(_byte_div)
{
    BruterInt index = br_arg_get(context, args, 1).i;
    BruterInt value = br_arg_get(context, args, 2).i;
    if (value == 0)
    {
        printf("BR_ERROR: division by zero in byte.div\n");
        return -1; // or handle error as needed
    }
    uint8_t *byte_ptr = br_arg_get(context, args, 0).p;
    byte_ptr[index] = byte_ptr[index] / value; // division by value
    return -1;
}

BR_INIT(byte)
{
    bruter_push_pointer(context, _byte_set, "byte.set", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, _byte_get, "byte.get", BR_TYPE_FUNCTION);
    
    bruter_push_pointer(context, _byte_add, "byte.add", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, _byte_sub, "byte.sub", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, _byte_mul, "byte.mul", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, _byte_div, "byte.div", BR_TYPE_FUNCTION);
}
