#include "br.h"

list_function(_label)
{
    free(context->keys[arg_i(0)]);
    context->keys[arg_i(1)] = str_duplicate(arg_s(0));
    return -1;
}

list_function(_ls)
{
    for (Int i = 0; i < context->size; i++)
    {
        if (data_l(i) != NULL)
        {
            printf("[%ld](\"%s\"):\t\t", i, data_l(i));
        }
        else
        {
            printf("[%ld](\"\"):\t\t", i);
        }

        printf(" %s\n", data_s(i));
    }
    return -1;
}

list_function(_return)
{
    if (args->size < 1)
    {
        return -1;
    }
    else
    {
        return arg_i(0);
    }
}

list_function(_ignore)
{
    return -1;
}

list_function(_repeat)
{
    Int times = arg(0).i;
    char* code = arg_s(1);
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

list_function(_forever)
{
    char* code = arg_s(0);
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

list_function(_get)
{
    return arg(0).i;
}

list_function(_set)
{
    Int index = arg(0).i;
    Int value = arg(1).i;
    context->data[index].i = value;
    return -1;
}

list_function(_eval)
{
    return eval(context, arg_s(0));
}

init(std)
{
    add_function(context, "label", _label);
    //add_function(context, "unlabel", _unlabel);
    //add_function(context, "rename", _rename);
    
    //add_function(context, "delete", _delete);
    
    add_function(context, "ls", _ls);
    
    add_function(context, "ignore", _ignore);

    add_function(context, "return", _return);

    add_function(context, "repeat", _repeat);
    add_function(context, "forever", _forever);

    add_function(context, "get", _get);
    add_function(context, "set", _set);

    add_function(context, "eval", _eval);
}