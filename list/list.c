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

BR_FUNCTION(brl_list_run)
{
    BruterList* list = (BruterList*)br_arg_get(context, args, 0).p;
    return bruter_run(list).i;
}

BR_INIT(list)
{
    br_add_function(context, "list.new", brl_list_new);
    br_add_function(context, "list.push", brl_list_push);
    br_add_function(context, "list.unshift", brl_list_unshift);
    br_add_function(context, "list.insert", brl_list_insert);
    br_add_function(context, "list.pop", brl_list_pop);
    br_add_function(context, "list.shift", brl_list_shift);
    br_add_function(context, "list.remove", brl_list_remove);
    br_add_function(context, "list.get", brl_list_get);
    br_add_function(context, "list.set", brl_list_set);
    br_add_function(context, "list.size", brl_list_size);
    br_add_function(context, "list.reverse", brl_list_reverse);
    br_add_function(context, "list.swap", brl_list_swap);
    br_add_function(context, "list.find", brl_list_find);
    br_add_function(context, "list.copy", brl_list_copy);
    br_add_function(context, "list.concat", brl_list_concat);
    br_add_function(context, "list.fast_remove", brl_list_fast_remove);
    br_add_function(context, "list.double", brl_list_double);
    br_add_function(context, "list.half", brl_list_half);
    br_add_function(context, "list.call", brl_list_call);
    br_add_function(context, "list.run", brl_list_run);
}