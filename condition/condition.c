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
    char* cond = ARG_P(0);
    char* true_part = ARG_P(1);
    char* false_part = NULL;

    if (ARG_COUNT() > 2)
        false_part = ARG_P(2);
    
    Int result = -1;

    // lets check if there is a parser variable in the program
    Int parser_index = list_find(context, VALUE(p, NULL), "parser");
    if (parser_index == -1)
    {
        printf("BRUTER_ERROR: parser not found, using basic parser\n");
        parser_index = new_var(context, "parser");
        context->data[parser_index].p = basic_parser();
    }
    else 
    {
        parser_index = context->data[parser_index].i;
    }
    List *parser = context->data[parser_index].p;

    if (cond == NULL)
    {
        result = 0;
    }
    else
    {
        result = eval(context, parser, cond);
    }

    if (result == 1)
    {
        result = eval(context, parser, true_part);
    }
    else if (false_part != NULL)
    {
        result = eval(context, parser, false_part);
    }
    else
    {
        result = 0;
    }
    return result;
}


INIT(math)
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