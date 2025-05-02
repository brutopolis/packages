#include "buxu.h"

function(_unlabel)
{
    free(data_l(arg(0).i));
    data_l(arg(0).i) = NULL;
    return -1;
}

function(_rename)
{
    char* name = arg_s(0);
    Int index = arg(1).i;
    if (data_l(index) != NULL)
    {
        free(data_l(index));
    }
    data_l(index) = str_duplicate(name);
    return -1;
}

function(_ls)
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

function(_repeat)
{
    Int times = arg(0).i;
    char* code = arg_s(1);
    Int result = -1;
    for (Int i = 0; i < times; i++)
    {
        result = eval(context, code);
        if (result != -1)
        {
            break;
        }
    }
    return result;
}

function(_forever)
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

function(_get)
{
    return arg(0).i;
}

function(_set)
{
    Int index = arg(0).i;
    Int value = arg(1).i;
    context->data[index].i = value;
    return -1;
}

init(std)
{
    add_function(context, "unlabel", _unlabel);
    add_function(context, "rename", _rename);

    add_function(context, "ls", _ls);
    add_function(context, "repeat", _repeat);
    add_function(context, "forever", _forever);

    add_function(context, "get", _get);
    add_function(context, "set", _set);
}