#include "br.h"

BRUTER_FUNCTION(_alloc_set_byte)
{
    uint8_t *allocd = BR_ARG(0).p;
    BruterInt index = BR_ARG(1).i;
    uint8_t value = BR_ARG(2).i;
    if (allocd == NULL)
    {
        printf("BR_ERROR: alloc_set_byte called with NULL pointer\n");
        return -1;
    }
    allocd[index] = value;
    return -1;
}

BRUTER_FUNCTION(_alloc_get_byte)
{
    uint8_t *allocd = BR_ARG(0).p;
    BruterInt index = BR_ARG(1).i;
    if (allocd == NULL)
    {
        printf("BR_ERROR: alloc_get_byte called with NULL pointer\n");
        return -1;
    }
    BruterInt result = br_new_var(context, NULL);
    bruter_set(context, result, BRUTER_VALUE(i, allocd[index]));
    return result;
}

BR_INIT(alloc)
{
    br_add_function(context, "alloc.byte.set", _alloc_set_byte);
    br_add_function(context, "alloc.byte.get", _alloc_get_byte);
}
