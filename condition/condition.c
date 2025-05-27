#include "br.h"

BRUTER_FUNCTION(_iequals)
{
    if (BR_ARG(0).i == BR_ARG(1).i)
        return 1;
    return 0;
}

BRUTER_FUNCTION(_inotequals)
{
    if (BR_ARG(0).i != BR_ARG(1).i)
        return 1;
    return 0;
}

BRUTER_FUNCTION(_ibigger)
{
    if (BR_ARG(0).i > BR_ARG(1).i)
        return 1;
    return 0;
}

BRUTER_FUNCTION(_ibiggerorequals)
{
    if (BR_ARG(0).i >= BR_ARG(1).i)
        return 1;
    return 0;
}

BRUTER_FUNCTION(_ilower)
{
    if (BR_ARG(0).i < BR_ARG(1).i)
        return 1;
    return 0;
}

BRUTER_FUNCTION(_ilowerorequals)
{
    if (BR_ARG(0).i <= BR_ARG(1).i)
        return 1;
    return 0;
}

BRUTER_FUNCTION(_fequals)
{
    if (BR_ARG(0).f == BR_ARG(1).f)
        return 1;
    return 0;
}

BRUTER_FUNCTION(_fnotequals)
{
    if (BR_ARG(0).f != BR_ARG(1).f)
        return 1;
    return 0;
}

BRUTER_FUNCTION(_fbigger)
{
    if (BR_ARG(0).f > BR_ARG(1).f)
        return 1;
    return 0;
}

BRUTER_FUNCTION(_fbiggerorequals)
{
    if (BR_ARG(0).f >= BR_ARG(1).f)
        return 1;
    return 0;
}

BRUTER_FUNCTION(_flower)
{
    if (BR_ARG(0).f < BR_ARG(1).f)
        return 1;
    return 0;
}

BRUTER_FUNCTION(_flowerorequals)
{
    if (BR_ARG(0).f <= BR_ARG(1).f)
        return 1;
    return 0;
}

BRUTER_FUNCTION(_if)
{
    char* cond = BR_ARG(0).s;
    char* true_part = BR_ARG(1).s;
    char* false_part = NULL;

    if (BR_ARG_COUNT() > 2)
        false_part = BR_ARG(2).s;
    
    BruterInt result = -1;

    // lets check if there is a parser variable in the program
    BruterInt parser_index = bruter_find(context, BRUTER_VALUE(p, NULL), "parser");
    if (parser_index == -1)
    {
        printf("BR_ERROR: parser not found, using basic parser\n");
        parser_index = br_new_var(context, "parser");
        context->data[parser_index].p = br_simple_parser();
    }
    else 
    {
        parser_index = context->data[parser_index].i;
    }
    BruterList *parser = context->data[parser_index].p;

    if (cond == NULL)
    {
        result = 0;
    }
    else
    {
        result = br_eval(context, parser, cond);
    }

    if (result == 1)
    {
        result = br_eval(context, parser, true_part);
    }
    else if (false_part != NULL)
    {
        result = br_eval(context, parser, false_part);
    }
    else
    {
        result = 0;
    }
    return result;
}


BR_INIT(math)
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