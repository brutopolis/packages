#include "br.h"

list_function(_str_concat)
{
    // concatenate two strings
    char *str1 = arg_s(0);
    char *str2 = arg_s(1);
    char *result = malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(result, str1);
    strcat(result, str2);
    Int result_i = new_string(context, result, NULL);
    free(result);
    return result_i;
}

list_function(_str_delete)
{
    Int len = strlen(arg_s(0));
    Int blocks = (len + 1 + sizeof(void*) - 1) / sizeof(void*);
    
    for (Int i = 0; i < blocks; i++)
    {
        list_remove(context, arg_i(0));
    }
    
    return 0;
}

list_function(_str_length)
{
    Int index = new_var(context, 0);
    data(index).i = strlen(arg_s(0));
    return index;
}

list_function(_str_find)
{
    Int index = new_var(context, 0);
    data(index).i = (Int)strstr(arg_s(0), arg_s(1)) - (Int)arg_s(0);
    return index;
}

list_function(_str_format)
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

    // create the new string inside context
    Int result_i = new_string(context, buffer, NULL);

    return result_i;
}


init(string)
{
    add_function(context, "string.concat", _str_concat);
    add_function(context, "string.delete", _str_delete);
    add_function(context, "string.length", _str_length);
    add_function(context, "string.find", _str_find);
    add_function(context, "string.format", _str_format);
}
