#include "buxu.h"

List* lists;

void ___atexit_free_lists()
{
    for (Int i = 0; i < lists->size; i++)
    {
        List *list = (List*)lists->data[i].p;
        list_free(list);
        free(list);
    }
    free(lists);
}

// list functions
// list functions
// list functions
// list functions

function(brl_std_list_new)
{
    Int index = new_var(vm, 0);
    lists->data[index].p = list_init(0);
    List *list = (List*)data(index).p;
    for (Int i = 0; i < args->size; i++)
    {
        list_push(list, (Value){.i = arg_i(i)});
    }
    list_push(lists, (Value){.p = list});
    return index;
}

function(brl_std_list_push)
{
    List *list = (List*)arg(0).p;
    for (Int i = 1; i < args->size; i++)
    {
        list_push(list, (Value){.i = arg_i(i)});
    }
    return -1;
}

function(brl_std_list_pop)
{
    List *list = (List*)arg(0).p;
    return list_pop(list).i;
}

function(brl_std_list_unshift)
{
    List *list = (List*)arg(0).p;
    for (Int i = 1; i < args->size; i++)
    {
        list_unshift(list, (Value){.i = arg_i(i)});
    }
    return -1;
}

function(brl_std_list_shift)
{
    List *list = (List*)arg(0).p;
    return list_shift(list).i;
}

function(std_list_insert)
{
    List *list = (List*)arg(0).p;
    Int index = arg(1).i;
    for (Int i = 2; i < args->size; i++)
    {
        list_insert(list, index, (Value){.i = arg_i(i)});
        index++;
    }
    return -1;
}

function(brl_std_list_remove)
{
    List *list = (List*)arg(0).p;
    Int index = arg(1).i;
    list_remove(list, index);
    return -1;
}

function(brl_std_list_set)
{
    List *list = (List*)arg(0).p;
    Int index = arg(1).i;
    list->data[index].i = arg_i(2);
    return -1;
}

function(brl_std_list_get)
{
    List *list = (List*)arg(0).p;
    Int index = arg(1).i;
    return list->data[index].i;
}

function(brl_std_list_len)
{
    List *list = (List*)arg(0).p;
    return list->size;
}

function(brl_std_list_free)
{
    List *list = (List*)arg(0).p;
    for (Int i = 0; i < lists->size; i++)
    {
        if (lists->data[i].p == list)
        {
            list_remove(lists, i);
            break;
        }
    }
    list_free(list);
    return -1;
}

function(brl_std_list_reverse)
{
    List *list = (List*)arg(0).p;
    list_reverse(list);
    return -1;
}

init(list)
{
    lists = new_list(vm);
    atexit(___atexit_free_lists); // remove lists at exit if not freed by user
    
    add_function(vm, "list.new", brl_std_list_new);
    add_function(vm, "list.push", brl_std_list_push);
    add_function(vm, "list.pop", brl_std_list_pop);
    add_function(vm, "list.unshift", brl_std_list_unshift);
    add_function(vm, "list.shift", brl_std_list_shift);
    add_function(vm, "list.insert", std_list_insert);
    add_function(vm, "list.remove", brl_std_list_remove);
    add_function(vm, "list.set", brl_std_list_set);
    add_function(vm, "list.get", brl_std_list_get);
    add_function(vm, "list.len", brl_std_list_len);
    add_function(vm, "list.free", brl_std_list_free);
    add_function(vm, "list.reverse", brl_std_list_reverse);
}