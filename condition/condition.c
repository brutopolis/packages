#include <bruter-representation.h>

BR_FUNCTION(_iequals)
{
    if (br_arg_get(context, args, 0).i == br_arg_get(context, args, 1).i)
        return 1;
    return 0;
}

BR_FUNCTION(_inotequals)
{
    if (br_arg_get(context, args, 0).i != br_arg_get(context, args, 1).i)
        return 1;
    return 0;
}

BR_FUNCTION(_ibigger)
{
    if (br_arg_get(context, args, 0).i > br_arg_get(context, args, 1).i)
        return 1;
    return 0;
}

BR_FUNCTION(_ibiggerorequals)
{
    if (br_arg_get(context, args, 0).i >= br_arg_get(context, args, 1).i)
        return 1;
    return 0;
}

BR_FUNCTION(_ilower)
{
    if (br_arg_get(context, args, 0).i < br_arg_get(context, args, 1).i)
        return 1;
    return 0;
}

BR_FUNCTION(_ilowerorequals)
{
    if (br_arg_get(context, args, 0).i <= br_arg_get(context, args, 1).i)
        return 1;
    return 0;
}

BR_FUNCTION(_fequals)
{
    if (br_arg_get(context, args, 0).f == br_arg_get(context, args, 1).f)
        return 1;
    return 0;
}

BR_FUNCTION(_fnotequals)
{
    if (br_arg_get(context, args, 0).f != br_arg_get(context, args, 1).f)
        return 1;
    return 0;
}

BR_FUNCTION(_fbigger)
{
    if (br_arg_get(context, args, 0).f > br_arg_get(context, args, 1).f)
        return 1;
    return 0;
}

BR_FUNCTION(_fbiggerorequals)
{
    if (br_arg_get(context, args, 0).f >= br_arg_get(context, args, 1).f)
        return 1;
    return 0;
}

BR_FUNCTION(_flower)
{
    if (br_arg_get(context, args, 0).f < br_arg_get(context, args, 1).f)
        return 1;
    return 0;
}

BR_FUNCTION(_flowerorequals)
{
    if (br_arg_get(context, args, 0).f <= br_arg_get(context, args, 1).f)
        return 1;
    return 0;
}

BR_FUNCTION(_if)
{
    char* cond = br_arg_get(context, args, 0).p;
    char* true_part = br_arg_get(context, args, 1).p;
    char* false_part = NULL;

    if (br_arg_get_count(args) > 2)
        false_part = br_arg_get(context, args, 2).p;
    
    BruterInt result = -1;

    BruterList *parser = br_get_parser(context);

    if (cond == NULL)
    {
        result = -1;
    }
    else
    {
        result = br_eval(context, cond);
    }

    if (result == 1)
    {
        result = br_eval(context, true_part);
    }
    else if (false_part != NULL)
    {
        result = br_eval(context, false_part);
    }
    else
    {
        result = -1;
    }
    return result;
}


BR_INIT(condition)
{
    br_add_function(context, "i==", _iequals);
    br_add_function(context, "i!=", _inotequals);
    br_add_function(context, "i>", _ibigger);
    br_add_function(context, "i>=", _ibiggerorequals);
    br_add_function(context, "i<", _ilower);
    br_add_function(context, "i<=", _ilowerorequals);
    
    br_add_function(context, "f==", _fequals);
    br_add_function(context, "f!=", _fnotequals);
    br_add_function(context, "f>", _fbigger);
    br_add_function(context, "f>=", _fbiggerorequals);
    br_add_function(context, "f<", _flower);
    br_add_function(context, "f<=", _flowerorequals);

    br_add_function(context, "if", _if);
}