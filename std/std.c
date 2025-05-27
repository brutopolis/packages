#include "br.h"

BRUTER_FUNCTION(_label)
{
    free(context->keys[BR_ARG_I(0)]);
    context->keys[BR_ARG_I(1)] = br_str_duplicate(BR_ARG(0).s);
    return -1;
}

BRUTER_FUNCTION(_ls)
{
    for (BruterInt i = 0; i < context->size; i++)
    {
        if (bruter_get_key(context, i) != NULL)
        {
            printf("[%ld](\"%s\"):\t\t", i, bruter_get_key(context, i));
        }
        else
        {
            printf("[%ld](\"\"):\t\t", i);
        }

        printf(" %ld\n", bruter_get(context, i).i);
    }
    return -1;
}

BRUTER_FUNCTION(_return)
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

BRUTER_FUNCTION(_ignore)
{
    return -1;
}

BRUTER_FUNCTION(_repeat)
{
    BruterInt times = BR_ARG(0).i;
    char* code = BR_ARG(1).s;
    BruterInt result = -1;

    BruterList *parser = br_get_parser(context);
    
    if (strchr(code, '(') != NULL) // do not optimize
    {
        for (BruterInt i = 0; i < times; i++)
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
        BruterList* compiled = br_compile_code(context, parser, code);
        
        for (BruterInt i = 0; i < times; i++)
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

BRUTER_FUNCTION(_forever)
{
    char* code = BR_ARG(0).s;
    BruterInt result = -1;

    BruterList *parser = br_get_parser(context);

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

BRUTER_FUNCTION(_get)
{
    return BR_ARG(0).i;
}

BRUTER_FUNCTION(_set)
{
    BruterInt index = BR_ARG(0).i;
    BruterInt value = BR_ARG(1).i;
    context->data[index].i = value;
    return -1;
}

BRUTER_FUNCTION(_eval)
{
    BruterList *parser = br_get_parser(context);

    return br_eval(context, parser, BR_ARG(0).s);
}

BRUTER_FUNCTION(_unlabel)
{
    free(context->keys[BR_ARG_I(0)]);
    context->keys[BR_ARG_I(0)] = NULL;
    return -1;
}

BRUTER_FUNCTION(_rename)
{
    free(context->keys[BR_ARG_I(0)]);
    context->keys[BR_ARG_I(0)] = br_str_duplicate(BR_ARG(1).s);
    return -1;
}

BRUTER_FUNCTION(_delete)
{
    free(context->keys[BR_ARG_I(0)]);
    context->keys[BR_ARG_I(0)] = NULL;

    BruterList* unused = br_get_unused(context);
    bruter_push(unused, BRUTER_VALUE(i, BR_ARG_I(0)), NULL);
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