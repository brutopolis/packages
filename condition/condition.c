#include "buxu.h"

list_function(_iequals)
{
    if (arg(0).i == arg(1).i)
        return 1;
    return 0;
}

list_function(_inotequals)
{
    if (arg(0).i != arg(1).i)
        return 1;
    return 0;
}

list_function(_ibigger)
{
    if (arg(0).i > arg(1).i)
        return 1;
    return 0;
}

list_function(_ibiggerorequals)
{
    if (arg(0).i >= arg(1).i)
        return 1;
    return 0;
}

list_function(_ilower)
{
    if (arg(0).i < arg(1).i)
        return 1;
    return 0;
}

list_function(_ilowerorequals)
{
    if (arg(0).i <= arg(1).i)
        return 1;
    return 0;
}

list_function(_fequals)
{
    if (arg(0).f == arg(1).f)
        return 1;
    return 0;
}

list_function(_fnotequals)
{
    if (arg(0).f != arg(1).f)
        return 1;
    return 0;
}

list_function(_fbigger)
{
    if (arg(0).f > arg(1).f)
        return 1;
    return 0;
}

list_function(_fbiggerorequals)
{
    if (arg(0).f >= arg(1).f)
        return 1;
    return 0;
}

list_function(_flower)
{
    if (arg(0).f < arg(1).f)
        return 1;
    return 0;
}

list_function(_flowerorequals)
{
    if (arg(0).f <= arg(1).f)
        return 1;
    return 0;
}

list_function(_if)
{
    char* cond = arg_s(0);
    char* true_part = arg_s(1);
    char* false_part = NULL;

    if (args->size > 2)
        false_part = arg_s(2);
    
    Int result = -1;

    if (cond == NULL)
    {
        result = 0;
    }
    else
    {
        result = eval(context, cond);
    }

    if (result == 1)
    {
        result = eval(context, true_part);
    }
    else if (false_part != NULL)
    {
        result = eval(context, false_part);
    }
    else
    {
        result = 0;
    }
    return result;
}


init(math)
{
    add_function(context, "i==", _iequals);
    add_function(context, "i!=", _inotequals);
    add_function(context, "i>", _ibigger);
    add_function(context, "i>=", _ibiggerorequals);
    add_function(context, "i<", _ilower);
    add_function(context, "i<=", _ilowerorequals);
    
    add_function(context, "f==", _fequals);
    add_function(context, "f!=", _fnotequals);
    add_function(context, "f>", _fbigger);
    add_function(context, "f>=", _fbiggerorequals);
    add_function(context, "f<", _flower);
    add_function(context, "f<=", _flowerorequals);

    add_function(context, "if", _if);
}