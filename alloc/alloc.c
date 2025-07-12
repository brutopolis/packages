#include <bruter-representation.h>

BR_FUNCTION(_alloc_set_byte)
{
    uint8_t *allocd = br_arg_get(context, args, 0).p;
    BruterInt index = br_arg_get(context, args, 1).i;
    uint8_t value = br_arg_get(context, args, 2).i;
    if (allocd == NULL)
    {
        printf("BR_ERROR: alloc_set_byte called with NULL pointer\n");
        return -1;
    }
    allocd[index] = value;
    return -1;
}

BR_FUNCTION(_alloc_get_byte)
{
    uint8_t *allocd = br_arg_get(context, args, 0).p;
    BruterInt index = br_arg_get(context, args, 1).i;
    if (allocd == NULL)
    {
        printf("BR_ERROR: alloc_get_byte called with NULL pointer\n");
        return -1;
    }
    BruterInt result = br_new_var(context, bruter_value_int(allocd[index]), NULL, BR_TYPE_ANY);
    return result;
}

BR_INIT(alloc)
{
    bruter_push_function(context, _alloc_set_byte, "alloc.byte_set", BR_TYPE_FUNCTION);
    bruter_push_function(context, _alloc_get_byte, "alloc.byte_get", BR_TYPE_FUNCTION);
}
