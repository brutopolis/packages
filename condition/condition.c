#include "br.h"

LIST_FUNCTION(_iequals)
{
    if (ARG(0).i == ARG(1).i)
        return 1;
    return 0;
}

LIST_FUNCTION(_inotequals)
{
    if (ARG(0).i != ARG(1).i)
        return 1;
    return 0;
}

LIST_FUNCTION(_ibigger)
{
    if (ARG(0).i > ARG(1).i)
        return 1;
    return 0;
}

LIST_FUNCTION(_ibiggerorequals)
{
    if (ARG(0).i >= ARG(1).i)
        return 1;
    return 0;
}

LIST_FUNCTION(_ilower)
{
    if (ARG(0).i < ARG(1).i)
        return 1;
    return 0;
}

LIST_FUNCTION(_ilowerorequals)
{
    if (ARG(0).i <= ARG(1).i)
        return 1;
    return 0;
}

LIST_FUNCTION(_fequals)
{
    if (ARG(0).f == ARG(1).f)
        return 1;
    return 0;
}

LIST_FUNCTION(_fnotequals)
{
    if (ARG(0).f != ARG(1).f)
        return 1;
    return 0;
}

LIST_FUNCTION(_fbigger)
{
    if (ARG(0).f > ARG(1).f)
        return 1;
    return 0;
}

LIST_FUNCTION(_fbiggerorequals)
{
    if (ARG(0).f >= ARG(1).f)
        return 1;
    return 0;
}

LIST_FUNCTION(_flower)
{
    if (ARG(0).f < ARG(1).f)
        return 1;
    return 0;
}

LIST_FUNCTION(_flowerorequals)
{
    if (ARG(0).f <= ARG(1).f)
        return 1;
    return 0;
}

LIST_FUNCTION(_if)
{
    char* cond = ARG_S(0);
    char* true_part = ARG_S(1);
    char* false_part = NULL;

    if (ARG_COUNT() > 2)
        false_part = ARG_S(2);
    
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


INIT(math)
{
    ADD_FUNCTION(context, "i==", _iequals);
    ADD_FUNCTION(context, "i!=", _inotequals);
    ADD_FUNCTION(context, "i>", _ibigger);
    ADD_FUNCTION(context, "i>=", _ibiggerorequals);
    ADD_FUNCTION(context, "i<", _ilower);
    ADD_FUNCTION(context, "i<=", _ilowerorequals);
    
    ADD_FUNCTION(context, "f==", _fequals);
    ADD_FUNCTION(context, "f!=", _fnotequals);
    ADD_FUNCTION(context, "f>", _fbigger);
    ADD_FUNCTION(context, "f>=", _fbiggerorequals);
    ADD_FUNCTION(context, "f<", _flower);
    ADD_FUNCTION(context, "f<=", _flowerorequals);

    ADD_FUNCTION(context, "if", _if);
}