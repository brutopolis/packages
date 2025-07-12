#include <bruter-representation.h>

BR_FUNCTION(brl_list_new)
{
    BruterList* list = bruter_new(sizeof(BruterValue), false, false);
    BruterInt result = br_new_var(context, bruter_value_pointer(list), NULL, BR_TYPE_LIST);
    for (BruterInt i = 0; i < br_arg_get_count(args); i++)
    {
        BruterValue value = br_arg_get(context, args, i);
        bruter_push(list, value, NULL, 0);
    }
    return result;
}

BR_FUNCTION(brl_list_push)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    bruter_push(list, bruter_value_int(br_arg_get_index(args, 1)), NULL, 0);
    return -1;
}

BR_FUNCTION(brl_list_unshift)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    bruter_unshift(list, bruter_value_int(br_arg_get_index(args, 1)), NULL, 0);
    return -1;
}

BR_FUNCTION(brl_list_insert)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    BruterInt index = br_arg_get(context, args, 1).i;
    bruter_insert(list, index, bruter_value_int(br_arg_get_index(args, 2)), NULL, 0);
    return -1;
}

BR_FUNCTION(brl_list_pop)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    return bruter_pop(list).i;
}

BR_FUNCTION(brl_list_shift)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    return bruter_shift(list).i;
}

BR_FUNCTION(brl_list_remove)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    BruterInt index = br_arg_get(context, args, 1).i;
    
    return bruter_remove(list, index).i;
}

BR_FUNCTION(brl_list_get)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    BruterInt index = br_arg_get(context, args, 1).i;
    
    return list->data[index].i;
}

BR_FUNCTION(brl_list_set)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    BruterInt index = br_arg_get(context, args, 1).i;
    
    list->data[index].i = br_arg_get(context, args, 2).i;
    return -1;
}

BR_FUNCTION(brl_list_size)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    BruterInt result = br_new_var(context, bruter_value_int(list->size), NULL, BR_TYPE_ANY);
    return result;
}

BR_FUNCTION(brl_list_reverse)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    bruter_reverse(list);
    return -1;
}

BR_FUNCTION(brl_list_swap)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    BruterInt index1 = br_arg_get(context, args, 1).i;
    BruterInt index2 = br_arg_get(context, args, 2).i;
    
    bruter_swap(list, index1, index2);
    return -1;
}

BR_FUNCTION(brl_list_find)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    BruterInt index = br_arg_get(context, args, 1).i;
    
    return bruter_find(list, bruter_value_int(index));
}

BR_FUNCTION(brl_list_find_key)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    const char* key = br_arg_get_key(context, args, 1);
    
    return bruter_find_key(list, key);
}

BR_FUNCTION(brl_list_copy)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    BruterList* copy = bruter_copy(list);
    BruterInt result = br_new_var(context, bruter_value_pointer(copy), NULL, BR_TYPE_LIST);
    return result;
}

BR_FUNCTION(brl_list_concat)
{
    BruterList* dest = (BruterList*)br_arg_get(context, args, 0).p;
    BruterList* src = (BruterList*)br_arg_get(context, args, 1).p;
    
    bruter_concat(dest, src);
    return -1;
}

BR_FUNCTION(brl_list_fast_remove)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    BruterInt index = br_arg_get(context, args, 1).i;
    
    return bruter_fast_remove(list, index).i;
}

BR_FUNCTION(brl_list_double)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    bruter_double(list);
    return -1;
}

BR_FUNCTION(brl_list_half)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    bruter_half(list);
    return -1;
}

BR_FUNCTION(brl_list_call)
{
    
    BruterList* sub_context = (BruterList*)br_arg_get(context, args, 0).p;
    BruterList* cmd = (BruterList*)br_arg_get(context, args, 1).p;
    

    return bruter_call(sub_context, cmd);
}
BR_INIT(list)
{
    bruter_push_function(context, brl_list_new, "list.new", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_push, "list.push", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_unshift, "list.unshift", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_insert, "list.insert", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_pop, "list.pop", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_shift, "list.shift", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_remove, "list.remove", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_get, "list.get", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_set, "list.set", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_size, "list.size", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_reverse, "list.reverse", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_swap, "list.swap", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_find, "list.find", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_copy, "list.copy", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_concat, "list.concat", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_fast_remove, "list.fast_remove", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_double, "list.double", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_half, "list.half", BR_TYPE_FUNCTION);
    bruter_push_function(context, brl_list_call, "list.call", BR_TYPE_FUNCTION);
}