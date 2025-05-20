#include "br.h"

LIST_FUNCTION(_label)
{
    free(context->keys[ARG_I(0)]);
    context->keys[ARG_I(1)] = str_duplicate(ARG_S(0));
    return -1;
}

LIST_FUNCTION(_ls)
{
    for (Int i = 0; i < context->size; i++)
    {
        if (DATA_L(i) != NULL)
        {
            printf("[%ld](\"%s\"):\t\t", i, DATA_L(i));
        }
        else
        {
            printf("[%ld](\"\"):\t\t", i);
        }

        printf(" %s\n", DATA_S(i));
    }
    return -1;
}

LIST_FUNCTION(_return)
{
    if (ARG_COUNT() < 1)
    {
        return -1;
    }
    else
    {
        return ARG_I(0);
    }
}

LIST_FUNCTION(_ignore)
{
    return -1;
}

LIST_FUNCTION(_repeat)
{
    Int times = ARG(0).i;
    char* code = ARG_S(1);
    Int result = -1;
    if (strchr(code, '(') != NULL) // do not optimize
    {
        for (Int i = 0; i < times; i++)
        {
            result = eval(context, code);
            if (result != -1)
            {
                break;
            }
        }
    }
    else
    {
        List* compiled = compile_code(context, code);
        
        for (Int i = 0; i < times; i++)
        {
            result = compiled_call(context, compiled);
            if (result != -1)
            {
                break;
            }
        }
        compiled_free(compiled);
    }

    return result;
}

LIST_FUNCTION(_forever)
{
    char* code = ARG_S(0);
    Int result = -1;
    while(1)
    {
        result = eval(context, code);
        if (result != -1)
        {
            break;
        }
    }
    return result;
}

LIST_FUNCTION(_get)
{
    return ARG(0).i;
}

LIST_FUNCTION(_set)
{
    Int index = ARG(0).i;
    Int value = ARG(1).i;
    context->data[index].i = value;
    return -1;
}

LIST_FUNCTION(_eval)
{
    return eval(context, ARG_S(0));
}

INIT(std)
{
    ADD_FUNCTION(context, "label", _label);
    //ADD_FUNCTION(context, "unlabel", _unlabel);
    //ADD_FUNCTION(context, "rename", _rename);
    
    //ADD_FUNCTION(context, "delete", _delete);
    
    ADD_FUNCTION(context, "ls", _ls);
    
    ADD_FUNCTION(context, "ignore", _ignore);

    ADD_FUNCTION(context, "return", _return);

    ADD_FUNCTION(context, "repeat", _repeat);
    ADD_FUNCTION(context, "forever", _forever);

    ADD_FUNCTION(context, "get", _get);
    ADD_FUNCTION(context, "set", _set);

    ADD_FUNCTION(context, "eval", _eval);
}