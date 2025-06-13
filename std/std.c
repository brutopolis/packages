#include <bruter-representation.h>

BR_FUNCTION(_key)
{
    free(context->keys[br_arg_index(args, 0)]);
    context->keys[br_arg_index(args, 1)] = br_str_duplicate(br_arg(context, args, 0).s);
    return -1;
}

BR_FUNCTION(_ls)
{
    for (BruterInt i = 0; i < context->size; i++)
    {
        if (bruter_get_key(context, i) != NULL)
        {
            printf("[%ld](\"%s\"):\t\t", i, bruter_get_key(context, i));
        }
        else
        {
            printf("[%ld](\"\"):\t\t", i);
        }

        printf(" %ld\n", bruter_get(context, i).i);
    }
    return -1;
}

BR_FUNCTION(_return)
{
    if (br_arg_count(args) < 1)
    {
        return -1;
    }
    else
    {
        return br_arg_index(args, 0);
    }
}

BR_FUNCTION(_ignore)
{
    return -1;
}

BR_FUNCTION(_repeat)
{
    BruterInt times = br_arg(context, args, 0).i;
    char* code = br_arg(context, args, 1).s;
    BruterInt result = -1;

    BruterList *parser = br_get_parser(context);
    
    if (strchr(code, '(') != NULL) // do not optimize
    {
        for (BruterInt i = 0; i < times; i++)
        {
            result = br_eval(context, parser, code);
            if (result != -1)
            {
                break;
            }
        }
    }
    else
    {
        BruterList* compiled = br_compile_code(context, parser, code);
        
        for (BruterInt i = 0; i < times; i++)
        {
            result = br_compiled_call(context, compiled);
            if (result != -1)
            {
                break;
            }
        }
        br_compiled_free(compiled);
    }

    return result;
}

BR_FUNCTION(_forever)
{
    char* code = br_arg(context, args, 0).s;
    BruterInt result = -1;

    BruterList *parser = br_get_parser(context);

    while(1)
    {
        result = br_eval(context, parser, code);
        if (result != -1)
        {
            break;
        }
    }
    return result;
}

BR_FUNCTION(_while)
{
    char *condition_code = br_arg(context, args, 0).s;
    char *code = br_arg(context, args, 1).s;
    BruterInt result = -1;
    BruterList *parser = br_get_parser(context);
    BruterInt condition_result = br_eval(context, parser, condition_code);
    while (condition_result == 1)
    {
        result = br_eval(context, parser, code);
        if (result != -1)
        {
            break;
        }
        condition_result = br_eval(context, parser, condition_code);
    }
    
    return result;
}

BR_FUNCTION(_get)
{
    return br_arg(context, args, 0).i;
}

BR_FUNCTION(_set)
{
    BruterInt index = br_arg(context, args, 0).i;
    BruterInt value = br_arg(context, args, 1).i;
    context->data[index].i = value;
    return -1;
}

BR_FUNCTION(_eval)
{
    BruterList *parser = br_get_parser(context);

    return br_eval(context, parser, br_arg(context, args, 0).s);
}

BR_FUNCTION(_unkey)
{
    free(context->keys[br_arg_index(args, 0)]);
    context->keys[br_arg_index(args, 0)] = NULL;
    return -1;
}

BR_FUNCTION(_rename)
{
    free(context->keys[br_arg_index(args, 0)]);
    context->keys[br_arg_index(args, 0)] = br_str_duplicate(br_arg(context, args, 1).s);
    return -1;
}

BR_FUNCTION(_delete)
{
    free(context->keys[br_arg_index(args, 0)]);
    context->keys[br_arg_index(args, 0)] = NULL;

    BruterList *allocs = br_get_allocs(context);
    BruterInt found = bruter_find(allocs, bruter_value_i(br_arg_index(args, 0)), NULL);
    if (found != -1)
    {
        // if the variable is in allocs, we need to free it
        free(bruter_fast_remove(allocs, found).p);
    }

    BruterList* unused = br_get_unused(context);
    bruter_push(unused, bruter_value_i(br_arg_index(args, 0)), NULL, 0);
    return -1;
}

void init_std(BruterList *context)
{
    br_add_function(context, "key", _key);
    br_add_function(context, "unkey", _unkey);
    br_add_function(context, "rename", _rename);
    
    br_add_function(context, "delete", _delete);
    
    br_add_function(context, "ls", _ls);
    
    br_add_function(context, "#", _ignore);

    br_add_function(context, "return", _return);

    br_add_function(context, "repeat", _repeat);
    br_add_function(context, "forever", _forever);
    br_add_function(context, "while", _while);

    br_add_function(context, "get", _get);
    br_add_function(context, "set", _set);

    br_add_function(context, "eval", _eval);
}