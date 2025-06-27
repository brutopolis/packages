#include <bruter-representation.h>

BR_FUNCTION(key)
{
    free(context->keys[br_arg_get_index(args, 0)]);
    context->keys[br_arg_get_index(args, 1)] = br_str_duplicate(br_arg_get(context, args, 0).p);
    return -1;
}

BR_FUNCTION(return_)
{
    if (br_arg_get_count(args) < 1)
    {
        return -1;
    }
    else
    {
        return br_arg_get_index(args, 0);
    }
}

BR_FUNCTION(ignore)
{
    return -1;
}

BR_FUNCTION(repeat)
{
    BruterInt times = br_arg_get(context, args, 0).i;
    char* code = br_arg_get(context, args, 1).p;
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
        BruterInt compiled = br_bake_code(context, parser, code);
        BruterList *compiled_list = (BruterList*)bruter_get(context, compiled).p;
        for (BruterInt i = 0; i < times; i++)
        {

            result = br_baked_call(context, compiled_list);
            if (result != -1)
            {
                break;
            }
        }
    }

    return result;
}

BR_FUNCTION(forever)
{
    char* code = br_arg_get(context, args, 0).p;
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

BR_FUNCTION(while_)
{
    char *condition_code = br_arg_get(context, args, 0).p;
    char *code = br_arg_get(context, args, 1).p;
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

BR_FUNCTION(set)
{
    BruterInt index = br_arg_get_index(args, 0);
    BruterInt value = br_arg_get(context, args, 1).i;
    context->data[index].i = value;
    return -1;
}

BR_FUNCTION(unkey)
{
    free(context->keys[br_arg_get_index(args, 0)]);
    context->keys[br_arg_get_index(args, 0)] = NULL;
    return -1;
}

BR_FUNCTION(rename_)
{
    free(context->keys[br_arg_get_index(args, 0)]);
    context->keys[br_arg_get_index(args, 0)] = br_str_duplicate(br_arg_get(context, args, 1).p);
    return -1;
}

BR_FUNCTION(delete)
{
    free(context->keys[br_arg_get_index(args, 0)]);
    context->keys[br_arg_get_index(args, 0)] = NULL;

    br_clear_var(context, br_arg_get_index(args, 0));
    bruter_push(br_get_unused(context), bruter_value_int(br_arg_get_index(args, 0)), NULL, 0);
    
    return -1;
}

BR_FUNCTION(bake)
{
    char *code = br_arg_get(context, args, 0).p;
    BruterList *parser = br_get_parser(context);
    BruterInt baked = br_bake_code(context, parser, code);
    if (baked == -1)
    {
        return -1; // error
    }
    return baked;
}

/*BR_FUNCTION(std_function)
{
    BruterList *parser = br_get_parser(context);
    bruter_unshift(parser, bruter_value_pointer(parser_function_arg), "std_function", 0);
    BruterInt baked = _bake(context, args);
    context->types[baked] = BR_TYPE_USER_FUNCTION; // set the type to function
    bruter_shift(parser); // remove the std_function from the parser
    return baked;
}*/

void init_std(BruterList *context)
{
    br_add_function(context, "name", key);
    br_add_function(context, "unname", unkey);
    br_add_function(context, "rename", rename_);
    
    br_add_function(context, "delete", delete);
        
    br_add_function(context, "#", ignore);

    br_add_function(context, "return", return_);

    br_add_function(context, "repeat", repeat);
    br_add_function(context, "forever", forever);
    br_add_function(context, "while", while_);

    br_add_function(context, "set", set);
    br_add_function(context, "bake", bake);
    //br_add_function(context, "function", std_function);
}