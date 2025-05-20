#include "br.h"

List* lists;

LIST_FUNCTION(brl_new_list)
{
    Int is_table;
    if (ARG_COUNT() == 0)
    {
        is_table = false;
    }
    else
    {
        is_table = ARG(0).i;
    }
    
    List* list = list_init(sizeof(void*), is_table);
    list_push(lists, (Value){.p = list}, NULL);
    Int result = new_var(context, NULL);
    DATA(result).p = list;
    return result;
}

LIST_FUNCTION(brl_delete_list)
{
    List* list = (List*)ARG(0).p;
    if (list == NULL)
    {
        return -1;
    }
    Int found = list_find(lists, VALUE(p, list), NULL);
    if (found != -1)
    {
        list_fast_remove(lists, found);
    }
    list_free(list);
    return 0;
}

LIST_FUNCTION(brl_list_push)
{
    List* list = (List*)ARG(0).p;
    char* key = NULL;
    if (ARG_COUNT() > 2)
    {
        key = ARG_S(2);
    }
    list_push(list, VALUE(i, ARG_I(1)), key);
    return -1;
}

LIST_FUNCTION(brl_list_unshift)
{
    List* list = (List*)ARG(0).p;
    char* key = NULL;
    if (ARG_COUNT() > 2)
    {
        key = ARG_S(2);
    }
    list_unshift(list, VALUE(i, ARG_I(1)), key);
    return -1;
}

LIST_FUNCTION(brl_list_insert)
{
    List* list = (List*)ARG(0).p;
    Int index = ARG_I(1);
    char* key = NULL;
    if (ARG_COUNT() > 3)
    {
        key = ARG_S(3);
    }
    list_insert(list, index, VALUE(i, ARG_I(2)), key);
    return -1;
}

LIST_FUNCTION(brl_list_pop)
{
    List* list = (List*)ARG(0).p;
    return list_pop(list).i;
}

LIST_FUNCTION(brl_list_shift)
{
    List* list = (List*)ARG(0).p;
    return list_shift(list).i;
}

LIST_FUNCTION(brl_list_remove)
{
    List* list = (List*)ARG(0).p;
    Int index = ARG_I(1);
    
    return list_remove(list, index).i;
}

LIST_FUNCTION(brl_list_get)
{
    List* list = (List*)ARG(0).p;
    Int index = ARG_I(1);
    
    return list->data[index].i;
}

LIST_FUNCTION(brl_list_set)
{
    List* list = (List*)ARG(0).p;
    Int index = ARG_I(1);
    
    list->data[index].i = ARG(2).i;
    return -1;
}

LIST_FUNCTION(brl_list_size)
{
    List* list = (List*)ARG(0).p;
    Int result = new_var(context, NULL);
    DATA(result).i = list->size;
    return result;
}

LIST_FUNCTION(brl_list_reverse)
{
    List* list = (List*)ARG(0).p;
    list_reverse(list);
    return -1;
}

LIST_FUNCTION(brl_list_swap)
{
    List* list = (List*)ARG(0).p;
    Int index1 = ARG_I(1);
    Int index2 = ARG_I(2);
    
    list_swap(list, index1, index2);
    return -1;
}

LIST_FUNCTION(brl_list_find)
{
    List* list = (List*)ARG(0).p;
    Int index = ARG_I(1);
    
    return list_find(list, VALUE(i, ARG_I(2)), NULL);
}

LIST_FUNCTION(brl_list_copy)
{
    List* list = (List*)ARG(0).p;
    List* copy = list_copy(list);
    Int result = new_var(context, NULL);
    DATA(result).p = copy;
    return result;
}

LIST_FUNCTION(brl_list_fast_remove)
{
    List* list = (List*)ARG(0).p;
    Int index = ARG_I(1);
    
    return list_fast_remove(list, index).i;
}

LIST_FUNCTION(brl_list_double)
{
    List* list = (List*)ARG(0).p;
    list_double(list);
    return -1;
}

LIST_FUNCTION(brl_list_half)
{
    List* list = (List*)ARG(0).p;
    list_half(list);
    return -1;
}

LIST_FUNCTION(brl_list_call)
{
    
    List* sub_context = (List*)ARG(0).p;
    List* cmd = (List*)ARG(1).p;
    

    return list_call(sub_context, cmd).i;
}

// at exit function
void _free_at_exit()
{
    if (lists->size > 0)
    {
        while (lists->size > 0)
        {
            list_free(list_pop(lists).p);
        }
    }
    list_free(lists);
}


INIT(list)
{
    lists = list_init(sizeof(void*), false);
    ADD_FUNCTION(context, "list.init", brl_new_list);
    ADD_FUNCTION(context, "list.free", brl_delete_list);
    ADD_FUNCTION(context, "list.push", brl_list_push);
    ADD_FUNCTION(context, "list.unshift", brl_list_unshift);
    ADD_FUNCTION(context, "list.insert", brl_list_insert);
    ADD_FUNCTION(context, "list.pop", brl_list_pop);
    ADD_FUNCTION(context, "list.shift", brl_list_shift);
    ADD_FUNCTION(context, "list.remove", brl_list_remove);
    ADD_FUNCTION(context, "list.get", brl_list_get);
    ADD_FUNCTION(context, "list.set", brl_list_set);
    ADD_FUNCTION(context, "list.size", brl_list_size);
    ADD_FUNCTION(context, "list.reverse", brl_list_reverse);
    ADD_FUNCTION(context, "list.swap", brl_list_swap);
    ADD_FUNCTION(context, "list.find", brl_list_find);
    ADD_FUNCTION(context, "list.copy", brl_list_copy);
    ADD_FUNCTION(context, "list.fast_remove", brl_list_fast_remove);
    ADD_FUNCTION(context, "list.double", brl_list_double);
    ADD_FUNCTION(context, "list.half", brl_list_half);
    ADD_FUNCTION(context, "list.call", brl_list_call);

    // at exit function
    atexit(_free_at_exit);
}