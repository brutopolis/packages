#include "br.h"

LIST_FUNCTION(_label)
{
    free(context->keys[ARG_I(0)]);
    context->keys[ARG_I(1)] = str_duplicate(ARG(0).s);
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

        printf(" %ld\n", DATA(i).i);
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
    char* code = ARG(1).s;
    Int result = -1;

    // lets check if there is a parser variable in the program
    Int parser_index = list_find(context, VALUE(p, NULL), "parser");
    if (parser_index == -1)
    {
        printf("BRUTER_ERROR: parser not found, using basic parser\n");
        parser_index = new_var(context, "parser");
        context->data[parser_index].p = basic_parser();
    }
    
    List *parser = context->data[parser_index].p;

    if (strchr(code, '(') != NULL) // do not optimize
    {
        for (Int i = 0; i < times; i++)
        {
            result = eval(context, parser, code);
            if (result != -1)
            {
                break;
            }
        }
    }
    else
    {
        List* compiled = compile_code(context, parser, code);
        
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
    char* code = ARG(0).s;
    Int result = -1;

    // lets check if there is a parser variable in the program
    Int parser_index = list_find(context, VALUE(p, NULL), "parser");
    if (parser_index == -1)
    {
        printf("BRUTER_ERROR: parser not found, using basic parser\n");
        parser_index = new_var(context, "parser");
        context->data[parser_index].p = basic_parser();
    }
    
    List *parser = context->data[parser_index].p;

    while(1)
    {
        result = eval(context, parser, code);
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
    // lets check if there is a parser variable in the program
    Int parser_index = list_find(context, VALUE(p, NULL), "parser");
    if (parser_index == -1)
    {
        printf("BRUTER_ERROR: parser not found, using simple parser\n");
        parser_index = new_var(context, "parser");
        context->data[parser_index].p = basic_parser();
    }
    
    List *parser = context->data[parser_index].p;

    return eval(context, parser, ARG(0).s);
}

LIST_FUNCTION(_unlabel)
{
    free(context->keys[ARG_I(0)]);
    context->keys[ARG_I(0)] = NULL;
    return -1;
}

LIST_FUNCTION(_rename)
{
    free(context->keys[ARG_I(0)]);
    context->keys[ARG_I(0)] = str_duplicate(ARG(1).s);
    return -1;
}

LIST_FUNCTION(_delete)
{
    free(context->keys[ARG_I(0)]);
    context->keys[ARG_I(0)] = NULL;
    return -1;
}

INIT(std)
{
    add_function(context, "label", _label);
    add_function(context, "unlabel", _unlabel);
    add_function(context, "rename", _rename);
    
    add_function(context, "delete", _delete);
    
    add_function(context, "ls", _ls);
    
    add_function(context, "ignore", _ignore);

    add_function(context, "return", _return);

    add_function(context, "repeat", _repeat);
    add_function(context, "forever", _forever);

    add_function(context, "get", _get);
    add_function(context, "set", _set);

    add_function(context, "eval", _eval);
}