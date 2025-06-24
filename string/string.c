#include <bruter-representation.h>

BR_FUNCTION(_string_concat)
{
    char* str1 = br_arg_get(context, args, 0).s;
    char* str2 = br_arg_get(context, args, 1).s;
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    
    char* result_str = malloc(len1 + len2 + 1);
    if (result_str == NULL) 
    {
        printf("BR_ERROR: Memory allocation failed\n");
        return -1;
    }
    
    strcpy(result_str, str1);
    strncpy(result_str + len1, str2, len2);
    result_str[len1 + len2] = '\0'; // Null-terminate the result string
    
    BruterInt result = br_new_var(context, bruter_value_p(result_str), NULL, BR_TYPE_BUFFER);

    return result;
}

BR_FUNCTION(_string_length)
{
    char* str = br_arg_get(context, args, 0).s;
    size_t length = strlen(str);
    
    BruterInt result = br_new_var(context, bruter_value_i(length), NULL, BR_TYPE_ANY);
    
    return result;
}

BR_FUNCTION(_string_compare)
{
    char* str1 = br_arg_get(context, args, 0).s;
    char* str2 = br_arg_get(context, args, 1).s;
    
    int cmp_result = strcmp(str1, str2);
    
    BruterInt result = br_new_var(context, bruter_value_i(cmp_result), NULL, BR_TYPE_ANY);
    
    return result;
}

BR_INIT(string)
{
    br_add_function(context, "string.concat", _string_concat);
    br_add_function(context, "string.length", _string_length);
    br_add_function(context, "string.compare", _string_compare);
}
