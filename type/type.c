#include <bruter-representation.h>

BR_FUNCTION(_type_set)
{
    BruterInt index = br_arg_get_index(args, 0);
    int8_t type =  br_arg_get(context, args, 1).i;

    if (index < 0 || index >= context->size)
    {
        printf("BR_ERROR: index %" PRIdPTR " out of range in list of size %" PRIdPTR " \n", index, context->size);
        return -1;
    }

    context->types[index] = type;
    return -1;
}

BR_FUNCTION(_type_get)
{
    BruterInt index = br_arg_get_index(args, 0);

    if (index < 0 || index >= context->size)
    {
        printf("BR_ERROR: index %" PRIdPTR " out of range in list of size %" PRIdPTR " \n", index, context->size);
        return -1;
    }

    return br_new_var(context, bruter_value_int(context->types[index]), NULL, BR_TYPE_ANY);
}

BR_INIT(type)
{
    bruter_push_pointer(context, _type_set, "type.set", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, _type_get, "type.get", BR_TYPE_FUNCTION);
}
