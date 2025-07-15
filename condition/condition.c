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
    bruter_push_function(context, _iequals, "i==", BR_TYPE_FUNCTION);
    bruter_push_function(context, _inotequals, "i!=", BR_TYPE_FUNCTION);
    bruter_push_function(context, _ibigger, "i>", BR_TYPE_FUNCTION);
    bruter_push_function(context, _ibiggerorequals, "i>=", BR_TYPE_FUNCTION);
    bruter_push_function(context, _ilower, "i<", BR_TYPE_FUNCTION);
    bruter_push_function(context, _ilowerorequals, "i<=", BR_TYPE_FUNCTION);
    
    bruter_push_function(context, _fequals, "f==", BR_TYPE_FUNCTION);
    bruter_push_function(context, _fnotequals, "f!=", BR_TYPE_FUNCTION);
    bruter_push_function(context, _fbigger, "f>", BR_TYPE_FUNCTION);
    bruter_push_function(context, _fbiggerorequals, "f>=", BR_TYPE_FUNCTION);
    bruter_push_function(context, _flower, "f<", BR_TYPE_FUNCTION);
    bruter_push_function(context, _flowerorequals, "f<=", BR_TYPE_FUNCTION);

    bruter_push_function(context, _if, "if", BR_TYPE_FUNCTION);
}