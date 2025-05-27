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
    return allocd[index];
}

BR_INIT(alloc)
{
    printf("BLANK PACKAGE, WILL BE REWRITTEN SOON\n");
}
