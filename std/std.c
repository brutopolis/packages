#include "buxu.h"

function(_label)
{
    char* label = arg_s(0);
    
    return -1;
}

function(_ls)
{
    for (Int i = 0; i < vm->values->size; i++)
    {
        if (data_l(i).i != 0)
        {
            printf("[%ld](\"%s\"):\t\t", i, data_l(i).u8);
        }
        else
        {
            printf("[%ld](\"\"):\t\t", i);
        }

        printf(" %s\n", data_s(i));
    }
    return -1;
}

function(_return)
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

function(_ignore)
{
    return -1;
}

function(_repeat)
{
    Int times = arg(0).i;
    char* code = arg_s(1);
    Int result = -1;
    for (Int i = 0; i < times; i++)
    {
        result = eval(vm, code);
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
        result = eval(vm, code);
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
    vm->values->data[index].i = value;
    return -1;
}

init(std)
{
    add_function(vm, "lbl", _label);
    //add_function(vm, "unlabel", _unlabel);
    //add_function(vm, "rename", _rename);
    
    //add_function(vm, "delete", _delete);
    
    add_function(vm, "ls", _ls);
    
    add_function(vm, "void", _ignore);

    add_function(vm, "return", _return);

    add_function(vm, "repeat", _repeat);
    add_function(vm, "forever", _forever);

    add_function(vm, "get", _get);
    add_function(vm, "set", _set);
}