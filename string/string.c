#include <bruter-representation.h>

BR_FUNCTION(_string_concat)
{
    char* str1 = br_arg_get(context, args, 0).p;
    char* str2 = br_arg_get(context, args, 1).p;
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
    
    BruterInt result = br_new_var(context, bruter_value_pointer(result_str), NULL, BR_TYPE_BUFFER);

    return result;
}

BR_FUNCTION(_string_length)
{
    char* str = br_arg_get(context, args, 0).p;
    size_t length = strlen(str);
    
    BruterInt result = br_new_var(context, bruter_value_int(length), NULL, BR_TYPE_ANY);
    
    return result;
}

BR_FUNCTION(_string_compare)
{
    char* str1 = br_arg_get(context, args, 0).p;
    char* str2 = br_arg_get(context, args, 1).p;
    
    int cmp_result = strcmp(str1, str2);
    
    BruterInt result = br_new_var(context, bruter_value_int(cmp_result), NULL, BR_TYPE_ANY);
    
    return result;
}

BR_INIT(string)
{
    bruter_push_function(context, _string_concat, "string.concat", BR_TYPE_FUNCTION);
    bruter_push_function(context, _string_length, "string.length", BR_TYPE_FUNCTION);
    bruter_push_function(context, _string_compare, "string.compare", BR_TYPE_FUNCTION);
}
