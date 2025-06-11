#include "bruter-representation.h"

BruterList* lists;

BR_FUNCTION(brl_new_list)
{
    BruterInt is_table;
    if (br_arg_count(args) == 0)
    {
        is_table = false;
    }
    else
    {
        is_table = br_arg(context, args, 0).i;
    }
    
    BruterList* list = bruter_init(sizeof(void*), is_table, false);
    bruter_push(lists, bruter_value_p(list), NULL);

    BruterInt result = br_new_var(context, bruter_value_p(list), NULL);
    return result;
}

BR_FUNCTION(brl_delete_list)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    if (list == NULL)
    {
        return -1;
    }
    BruterInt found = bruter_find(lists, bruter_value_p(list), NULL);
    if (found != -1)
    {
        bruter_fast_remove(lists, found);
    }
    bruter_free(list);
    return 0;
}

BR_FUNCTION(brl_list_push)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    char* key = NULL;
    if (br_arg_count(args) > 2)
    {
        key = br_arg(context, args, 2).s;
    }
    bruter_push(list, bruter_value_i(br_arg_index(args, 1)), key);
    return -1;
}

BR_FUNCTION(brl_list_unshift)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    char* key = NULL;
    if (br_arg_count(args) > 2)
    {
        key = br_arg(context, args, 2).s;
    }
    bruter_unshift(list, bruter_value_i(bruter_get(args,1).i), key);
    return -1;
}

BR_FUNCTION(brl_list_insert)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    BruterInt index = br_arg_index(args, 1);
    char* key = NULL;
    if (br_arg_count(args) > 3)
    {
        key = br_arg(context, args, 3).s;
    }
    bruter_insert(list, index, bruter_value_i(bruter_get(args,2).i), key);
    return -1;
}

BR_FUNCTION(brl_list_pop)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    return bruter_pop(list).i;
}

BR_FUNCTION(brl_list_shift)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    return bruter_shift(list).i;
}

BR_FUNCTION(brl_list_remove)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    BruterInt index = br_arg_index(args, 1);
    
    return bruter_remove(list, index).i;
}

BR_FUNCTION(brl_list_get)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    BruterInt index = br_arg_index(args, 1);
    
    return list->data[index].i;
}

BR_FUNCTION(brl_list_set)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    BruterInt index = br_arg_index(args, 1);
    
    list->data[index].i = br_arg(context, args, 2).i;
    return -1;
}

BR_FUNCTION(brl_list_size)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    BruterInt result = br_new_var(context, bruter_value_i(list->size), NULL);
    return result;
}

BR_FUNCTION(brl_list_reverse)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    bruter_reverse(list);
    return -1;
}

BR_FUNCTION(brl_list_swap)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    BruterInt index1 = br_arg_index(args, 1);
    BruterInt index2 = br_arg_index(args, 2);
    
    bruter_swap(list, index1, index2);
    return -1;
}

BR_FUNCTION(brl_list_find)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    BruterInt index = br_arg_index(args, 1);
    
    return bruter_find(list, bruter_value_i(index), NULL);
}

BR_FUNCTION(brl_list_copy)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    BruterList* copy = bruter_copy(list);
    BruterInt result = br_new_var(context, bruter_value_p(copy), NULL);
    return result;
}

BR_FUNCTION(brl_list_concat)
{
    BruterList* dest = (BruterList*)br_arg(context, args, 0).p;
    BruterList* src = (BruterList*)br_arg(context, args, 1).p;
    
    bruter_concat(dest, src);
    return -1;
}

BR_FUNCTION(brl_list_fast_remove)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    BruterInt index = br_arg_index(args, 1);
    
    return bruter_fast_remove(list, index).i;
}

BR_FUNCTION(brl_list_double)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    bruter_double(list);
    return -1;
}

BR_FUNCTION(brl_list_half)
{
    BruterList* list = (BruterList*)br_arg(context, args, 0).p;
    bruter_half(list);
    return -1;
}

BR_FUNCTION(brl_list_call)
{
    
    BruterList* sub_context = (BruterList*)br_arg(context, args, 0).p;
    BruterList* cmd = (BruterList*)br_arg(context, args, 1).p;
    

    return bruter_call(sub_context, cmd).i;
}

// at exit function
void _free_at_exit()
{
    if (lists->size > 0)
    {
        while (lists->size > 0)
        {
            bruter_free(bruter_pop(lists).p);
        }
    }
    bruter_free(lists);
}


BR_INIT(list)
{
    lists = bruter_init(sizeof(void*), false, false);
    br_add_function(context, "list.init", brl_new_list);
    br_add_function(context, "list.free", brl_delete_list);
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

    // at exit function
    atexit(_free_at_exit);
}