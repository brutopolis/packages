#include "buxu.h"

function(_str_concat)
{
    // concatenate two strings
    char *str1 = arg_s(0);
    char *str2 = arg_s(1);
    char *result = malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(result, str1);
    strcat(result, str2);
    Int result_i = new_string(vm, NULL, result);
    free(result);
    return result_i;
}

function(_str_delete)
{
    Int len = strlen(arg_s(0));
    Int blocks = (len + 1 + sizeof(void*) - 1) / sizeof(void*);
    
    for (Int i = 0; i < blocks; i++)
    {
        list_remove(vm->values, arg_i(0));
        list_remove(vm->labels, arg_i(0));
    }

    for (Int i = arg_i(0) + 1; i < vm->labels->size; i++)
    {
        if (vm->labels->data[i].i > -1)
        {
            vm->labels->data[i].i -= blocks;
        }
    }
    return 0;
}

function(_str_length)
{
    Int index = new_var(vm, 0);
    data(index).i = strlen(arg_s(0));
    return index;
}

function(_str_find)
{
    Int index = new_var(vm, 0);
    data(index).i = (Int)strstr(arg_s(0), arg_s(1)) - (Int)arg_s(0);
    return index;
}

function(_str_format)
{
    // get the format string
    char *format = arg_s(0);

    // allocate a buffer for the formatted string
    char buffer[1024];

    // now, manually replace the format specifiers
    // your engine probably only needs very simple %s or %d replacement

    char *out = buffer;
    char *in = format;
    Int arg_index = 1; // start from second argument

    while (*in)
    {
        if (*in == '%' && (*(in + 1) == 's' || *(in + 1) == 'd'))
        {
            if (*(in + 1) == 's')
            {
                // string argument
                char *arg = arg_s(arg_index++);
                out += sprintf(out, "%s", arg);
            }
            else if (*(in + 1) == 'd')
            {
                // integer argument
                Int arg = arg_i(arg_index++);
                out += sprintf(out, "%d", arg);
            }
            in += 2;
        }
        else
        {
            *out++ = *in++;
        }
    }

    *out = '\0'; // terminate the string

    // create the new string inside vm
    Int result_i = new_string(vm, NULL, buffer);

    return result_i;
}


init(string)
{
    add_function(vm, "sca", _str_concat);
    add_function(vm, "del", _str_delete);
    add_function(vm, "len", _str_length);
    add_function(vm, "fnd", _str_find);
    add_function(vm, "frm", _str_format);
}
