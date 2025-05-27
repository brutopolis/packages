#include "br.h"

BruterList* lists;

BRUTER_FUNCTION(brl_new_list)
{
    BruterInt is_table;
    if (BR_ARG_COUNT() == 0)
    {
        is_table = false;
    }
    else
    {
        is_table = BR_ARG(0).i;
    }
    
    BruterList* list = bruter_init(sizeof(void*), is_table);
    bruter_push(lists, (BruterValue){.p = list}, NULL);
    BruterInt result = br_new_var(context, NULL);
    BR_DATA(result).p = list;
    return result;
}

BRUTER_FUNCTION(brl_delete_list)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    if (list == NULL)
    {
        return -1;
    }
    BruterInt found = bruter_find(lists, BRUTER_VALUE(p, list), NULL);
    if (found != -1)
    {
        bruter_fast_remove(lists, found);
    }
    bruter_free(list);
    return 0;
}

BRUTER_FUNCTION(brl_bruter_push)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    char* key = NULL;
    if (BR_ARG_COUNT() > 2)
    {
        key = BR_ARG(2).s;
    }
    bruter_push(list, BRUTER_VALUE(i, BR_ARG_I(1)), key);
    return -1;
}

BRUTER_FUNCTION(brl_bruter_unshift)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    char* key = NULL;
    if (BR_ARG_COUNT() > 2)
    {
        key = BR_ARG(2).s;
    }
    bruter_unshift(list, BRUTER_VALUE(i, BR_ARG_I(1)), key);
    return -1;
}

BRUTER_FUNCTION(brl_bruter_insert)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    BruterInt index = BR_ARG_I(1);
    char* key = NULL;
    if (BR_ARG_COUNT() > 3)
    {
        key = BR_ARG(3).s;
    }
    bruter_insert(list, index, BRUTER_VALUE(i, BR_ARG_I(2)), key);
    return -1;
}

BRUTER_FUNCTION(brl_bruter_pop)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    return bruter_pop(list).i;
}

BRUTER_FUNCTION(brl_bruter_shift)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    return bruter_shift(list).i;
}

BRUTER_FUNCTION(brl_bruter_remove)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    BruterInt index = BR_ARG_I(1);
    
    return bruter_remove(list, index).i;
}

BRUTER_FUNCTION(brl_bruter_get)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    BruterInt index = BR_ARG_I(1);
    
    return list->data[index].i;
}

BRUTER_FUNCTION(brl_bruter_set)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    BruterInt index = BR_ARG_I(1);
    
    list->data[index].i = BR_ARG(2).i;
    return -1;
}

BRUTER_FUNCTION(brl_bruter_size)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    BruterInt result = br_new_var(context, NULL);
    BR_DATA(result).i = list->size;
    return result;
}

BRUTER_FUNCTION(brl_bruter_reverse)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    bruter_reverse(list);
    return -1;
}

BRUTER_FUNCTION(brl_bruter_swap)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    BruterInt index1 = BR_ARG_I(1);
    BruterInt index2 = BR_ARG_I(2);
    
    bruter_swap(list, index1, index2);
    return -1;
}

BRUTER_FUNCTION(brl_bruter_find)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    BruterInt index = BR_ARG_I(1);
    
    return bruter_find(list, BRUTER_VALUE(i, BR_ARG_I(2)), NULL);
}

BRUTER_FUNCTION(brl_bruter_copy)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    BruterList* copy = bruter_copy(list);
    BruterInt result = br_new_var(context, NULL);
    BR_DATA(result).p = copy;
    return result;
}

BRUTER_FUNCTION(brl_bruter_fast_remove)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    BruterInt index = BR_ARG_I(1);
    
    return bruter_fast_remove(list, index).i;
}

BRUTER_FUNCTION(brl_bruter_double)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    bruter_double(list);
    return -1;
}

BRUTER_FUNCTION(brl_bruter_half)
{
    BruterList* list = (BruterList*)BR_ARG(0).p;
    bruter_half(list);
    return -1;
}

BRUTER_FUNCTION(brl_bruter_call)
{
    
    BruterList* sub_context = (BruterList*)BR_ARG(0).p;
    BruterList* cmd = (BruterList*)BR_ARG(1).p;
    

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
    lists = bruter_init(sizeof(void*), false);
    br_add_function(context, "list.init", brl_new_list);
    br_add_function(context, "list.free", brl_delete_list);
    br_add_function(context, "list.push", brl_bruter_push);
    br_add_function(context, "list.unshift", brl_bruter_unshift);
    br_add_function(context, "list.insert", brl_bruter_insert);
    br_add_function(context, "list.pop", brl_bruter_pop);
    br_add_function(context, "list.shift", brl_bruter_shift);
    br_add_function(context, "list.remove", brl_bruter_remove);
    br_add_function(context, "list.get", brl_bruter_get);
    br_add_function(context, "list.set", brl_bruter_set);
    br_add_function(context, "list.size", brl_bruter_size);
    br_add_function(context, "list.reverse", brl_bruter_reverse);
    br_add_function(context, "list.swap", brl_bruter_swap);
    br_add_function(context, "list.find", brl_bruter_find);
    br_add_function(context, "list.copy", brl_bruter_copy);
    br_add_function(context, "list.fast_remove", brl_bruter_fast_remove);
    br_add_function(context, "list.double", brl_bruter_double);
    br_add_function(context, "list.half", brl_bruter_half);
    br_add_function(context, "list.call", brl_bruter_call);

    // at exit function
    atexit(_free_at_exit);
}