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

init(string)
{
    add_function(vm, "string.concat", _str_concat);
}
