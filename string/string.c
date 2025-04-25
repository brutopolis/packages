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

function(_str_format)
{
    char* fmt = arg_s(0);
    int argc = args->size;
    int arg_index = 1;

    Int size = 0;
    Int capacity = sizeof(void*);
    Int blocks = 1;

    Int str_index = new_block(vm, NULL, blocks);
    char *buffer = (char*)&vm->values->data[str_index].u8[0];

    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++;
            char tmp[64]; // temp buffer for sprintf
            int len = 0;

            if (*fmt == 's' && arg_index < argc)
            {
                char *s = arg_s(arg_index++);
                len = strlen(s);
                // aumenta buffer se necessário
                while (size + len + 1 > capacity)
                {
                    list_push(vm->values, (Value){.i = 0});
                    list_push(vm->labels, (Value){.s = NULL});
                    capacity += sizeof(void*);
                }
                memcpy(buffer + size, s, len);
                size += len;
            }
            else if (*fmt == 'c' && arg_index < argc)
            {
                char c = (char)arg(arg_index++).i;
                if (size + 1 + 1 > capacity)
                {
                    list_push(vm->values, (Value){.i = 0});
                    list_push(vm->labels, (Value){.s = NULL});
                    capacity += sizeof(void*);
                }
                buffer[size++] = c;
            }
            else if (*fmt == 'd' && arg_index < argc)
            {
                len = sprintf(tmp, "%ld", (long)arg(arg_index++).i);
                while (size + len + 1 > capacity)
                {
                    list_push(vm->values, (Value){.i = 0});
                    list_push(vm->labels, (Value){.s = NULL});
                    capacity += sizeof(void*);
                }
                memcpy(buffer + size, tmp, len);
                size += len;
            }
            else if (*fmt == 'f' && arg_index < argc)
            {
                len = sprintf(tmp, "%f", arg(arg_index++).f);
                while (size + len + 1 > capacity)
                {
                    list_push(vm->values, (Value){.i = 0});
                    list_push(vm->labels, (Value){.s = NULL});
                    capacity += sizeof(void*);
                }
                memcpy(buffer + size, tmp, len);
                size += len;
            }
            else if (*fmt == 'p' && arg_index < argc)
            {
                len = sprintf(tmp, "%p", arg(arg_index++).p);
                while (size + len + 1 > capacity)
                {
                    list_push(vm->values, (Value){.i = 0});
                    list_push(vm->labels, (Value){.s = NULL});
                    capacity += sizeof(void*);
                }
                memcpy(buffer + size, tmp, len);
                size += len;
            }
            fmt++;
        }
        else if (*fmt == '\\')
        {
            fmt++;
            char c = *fmt++;
            if (c == 'n') c = '\n';
            else if (c == 't') c = '\t';
            else if (c == 'r') c = '\r';
            else /* default */;

            if (size + 1 + 1 > capacity)
            {
                list_push(vm->values, (Value){.i = 0});
                list_push(vm->labels, (Value){.s = NULL});
                capacity += sizeof(void*);
            }
            buffer[size++] = c;
        }
        else
        {
            if (size + 1 + 1 > capacity)
            {
                list_push(vm->values, (Value){.i = 0});
                list_push(vm->labels, (Value){.s = NULL});
                capacity += sizeof(void*);
            }
            buffer[size++] = *fmt++;
        }
    }

    buffer[size] = '\0';

    return str_index;
}

function(_str_len)
{
    char *str = arg_s(0);
    Int len = strlen(str);
    Int index = new_var(vm, NULL);
    arg(index).i = len;
    return index;
}

function(_str_block_len)
{
    Int index = arg(0).i;
    Int len = (strlen((char*)&vm->values->data[index].u8[0]) + 1 + sizeof(void*) - 1) / sizeof(void*);
    Int new_index = new_var(vm, NULL);
    arg(new_index).i = len;
    return new_index;
}

function(_str_sub)
{
    char *str = arg_s(0);
    Int start = arg(1).i;
    Int end = arg(2).i;

    if (start < 0)
    {
        start = strlen(str) + start;
    }

    if (end < 0)
    {
        end = strlen(str) + end;
    }

    if (start > end)
    {
        return -1;
    }

    Int len = end - start + 1;

    Int new_index = new_block(vm, NULL, len);

    memmove(&vm->values->data[new_index].u8[0], str + start, len);
    vm->values->data[new_index].u8[len] = '\0';

    data_l(new_index) = arg_l(0);
    arg_l(0) = NULL;

    return new_index;
}

function(_str_find)
{
    char *str = arg_s(0);
    char *substr = arg_s(1);

    char *found = strstr(str, substr);
    if (found)
    {
        Int index = new_var(vm, NULL);
        arg(index).i = found - str;
        return index;
    }
    else
    {
        return -1;
    }
}

init(string)
{
    add_function(vm, "string.set", _str_set);
    add_function(vm, "string.format", _str_format);
    add_function(vm, "string.concat", _str_concat);
    add_function(vm, "string.len", _str_len);
    add_function(vm, "string.lenb", _str_block_len);
    add_function(vm, "string.sub", _str_sub);
    add_function(vm, "string.find", _str_find);
}
