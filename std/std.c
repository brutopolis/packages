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
            result = br_eval(context, code);
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

    while(1)
    {
        result = br_eval(context, code);
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
    BruterInt condition_result = br_eval(context, condition_code);
    while (condition_result == 1)
    {
        result = br_eval(context, code);
        if (result != -1)
        {
            break;
        }
        condition_result = br_eval(context, condition_code);
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

void init_std(BruterList *context)
{
    bruter_push_function(context, key, "name", BR_TYPE_FUNCTION);
    bruter_push_function(context, unkey, "unname", BR_TYPE_FUNCTION);
    bruter_push_function(context, rename_, "rename", BR_TYPE_FUNCTION);
    
    bruter_push_function(context, delete, "delete", BR_TYPE_FUNCTION);
        
    bruter_push_function(context, ignore, "#", BR_TYPE_FUNCTION);

    bruter_push_function(context, return_, "return", BR_TYPE_FUNCTION);

    bruter_push_function(context, repeat, "repeat", BR_TYPE_FUNCTION);
    bruter_push_function(context, forever, "forever", BR_TYPE_FUNCTION);
    bruter_push_function(context, while_, "while", BR_TYPE_FUNCTION);

    bruter_push_function(context, set, "set", BR_TYPE_FUNCTION);
    bruter_push_function(context, bake, "bake", BR_TYPE_FUNCTION);
}