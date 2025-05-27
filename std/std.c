#include "br.h"

LIST_FUNCTION(_label)
{
    free(context->keys[BR_ARG_I(0)]);
    context->keys[BR_ARG_I(1)] = str_duplicate(BR_ARG(0).s);
    return -1;
}

LIST_FUNCTION(_ls)
{
    for (Int i = 0; i < context->size; i++)
    {
        if (BR_DATA_L(i) != NULL)
        {
            printf("[%ld](\"%s\"):\t\t", i, BR_DATA_L(i));
        }
        else
        {
            printf("[%ld](\"\"):\t\t", i);
        }

        printf(" %ld\n", BR_DATA(i).i);
    }
    return -1;
}

LIST_FUNCTION(_return)
{
    if (BR_ARG_COUNT() < 1)
    {
        return -1;
    }
    else
    {
        return BR_ARG_I(0);
    }
}

LIST_FUNCTION(_ignore)
{
    return -1;
}

LIST_FUNCTION(_repeat)
{
    Int times = BR_ARG(0).i;
    char* code = BR_ARG(1).s;
    Int result = -1;

    List *parser = br_get_parser(context);
    
    if (strchr(code, '(') != NULL) // do not optimize
    {
        for (Int i = 0; i < times; i++)
        {
            result = br_eval(context, parser, code);
            if (result != -1)
            {
                break;
            }
        }
    }
    else
    {
        List* compiled = br_compile_code(context, parser, code);
        
        for (Int i = 0; i < times; i++)
        {
            result = br_compiled_call(context, compiled);
            if (result != -1)
            {
                break;
            }
        }
        br_compiled_free(compiled);
    }

    return result;
}

LIST_FUNCTION(_forever)
{
    char* code = BR_ARG(0).s;
    Int result = -1;

    List *parser = br_get_parser(context);

    while(1)
    {
        result = br_eval(context, parser, code);
        if (result != -1)
        {
            break;
        }
    }
    return result;
}

LIST_FUNCTION(_get)
{
    return BR_ARG(0).i;
}

LIST_FUNCTION(_set)
{
    Int index = BR_ARG(0).i;
    Int value = BR_ARG(1).i;
    context->data[index].i = value;
    return -1;
}

LIST_FUNCTION(_eval)
{
    List *parser = br_get_parser(context);

    return br_eval(context, parser, BR_ARG(0).s);
}

LIST_FUNCTION(_unlabel)
{
    free(context->keys[BR_ARG_I(0)]);
    context->keys[BR_ARG_I(0)] = NULL;
    return -1;
}

LIST_FUNCTION(_rename)
{
    free(context->keys[BR_ARG_I(0)]);
    context->keys[BR_ARG_I(0)] = str_duplicate(BR_ARG(1).s);
    return -1;
}

LIST_FUNCTION(_delete)
{
    free(context->keys[BR_ARG_I(0)]);
    context->keys[BR_ARG_I(0)] = NULL;
    return -1;
}

BR_INIT(std)
{
    br_add_function(context, "label", _label);
    br_add_function(context, "unlabel", _unlabel);
    br_add_function(context, "rename", _rename);
    
    br_add_function(context, "delete", _delete);
    
    br_add_function(context, "ls", _ls);
    
    br_add_function(context, "ignore", _ignore);

    br_add_function(context, "return", _return);

    br_add_function(context, "repeat", _repeat);
    br_add_function(context, "forever", _forever);

    br_add_function(context, "get", _get);
    br_add_function(context, "set", _set);

    br_add_function(context, "eval", _eval);
}