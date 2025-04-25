#include "buxu.h"

function(_str_concat)
{
    char *str1 = arg_s(0);
    char *str2 = arg_s(1);

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    
    int total_len = len1 + len2 + 1;
    Int blocks = (total_len + sizeof(void*) - 1) / sizeof(void*);
    Int new_index = new_block(vm, NULL, blocks);

    memmove(&vm->values->data[new_index].u8[0], str1, len1);
    memmove(&vm->values->data[new_index].u8[len1], str2, len2);
    vm->values->data[new_index].u8[len1 + len2] = '\0';

    data_l(new_index) = arg_l(0);
    arg_l(0) = NULL;

    Int str1_blocks = (strlen(str1) + 1 + sizeof(void*) - 1) / sizeof(void*);

    for (Int i = 0; i < str1_blocks; i++)
    {
        list_remove(vm->values, arg_i(0));
        list_remove(vm->labels, arg_i(0));
    }

    return -1;
}

function(_str_set)
{
    char *str = arg_s(0);

    Int position = arg(1).i;

    char *content = arg_s(2);
    Int content_len = strlen(content);

    Int oldsize = strlen(str);

    Int end_pos = position + content_len;

    Int oldblocks = (oldsize + 1 + sizeof(void*) - 1) / sizeof(void*);
    Int needed_blocks = (end_pos + 1 + sizeof(void*) - 1) / sizeof(void*);

    if (needed_blocks <= oldblocks)
    {
        memmove(&str[position], content, content_len);
    }
    else
    {
        Int new_index = new_block(vm, NULL, needed_blocks);

        memmove(&vm->values->data[new_index].u8[0], str, position);
        memmove(&vm->values->data[new_index].u8[position], content, content_len);

        if (oldsize > end_pos)
        {
            memmove(&vm->values->data[new_index].u8[end_pos], str + end_pos, oldsize - end_pos);
        }

        vm->values->data[new_index].u8[
            (oldsize > end_pos ? oldsize : end_pos)
        ] = '\0';

        data_l(new_index) = arg_l(0);
        arg_l(0) = NULL;

        for (Int i = 0; i < oldblocks; i++)
        {
            list_remove(vm->values, arg_i(0));
            list_remove(vm->labels, arg_i(0));
        }

        arg_i(0) = new_index;
    }

    return -1;
}


init(str)
{
    add_function(vm, "string.concat", _str_concat);
    add_function(vm, "string.set", _str_set);
}
