#include "bruter-representation.h"

BR_FUNCTION(_alloc_set_byte)
{
    uint8_t *allocd = br_arg(context, args, 0).p;
    BruterInt index = br_arg(context, args, 1).i;
    uint8_t value = br_arg(context, args, 2).i;
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
    uint8_t *allocd = br_arg(context, args, 0).p;
    BruterInt index = br_arg(context, args, 1).i;
    if (allocd == NULL)
    {
        printf("BR_ERROR: alloc_get_byte called with NULL pointer\n");
        return -1;
    }
    BruterInt result = br_new_var(context, bruter_value_i(allocd[index]), NULL);
    return result;
}

BR_INIT(alloc)
{
    br_add_function(context, "alloc.byte.set", _alloc_set_byte);
    br_add_function(context, "alloc.byte.get", _alloc_get_byte);
}
