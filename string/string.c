#include "bruter-representation.h"

BR_FUNCTION(_string_concat)
{
    char* str1 = br_arg(context, args, 0).s;
    char* str2 = br_arg(context, args, 1).s;
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
    
    BruterInt result = br_new_var(context, bruter_value_p(result_str), NULL);

    BruterList *allocs = br_get_allocs(context);
    bruter_push(allocs, bruter_value_p(result_str), NULL);
    
    return result;
}

BR_FUNCTION(_string_length)
{
    char* str = br_arg(context, args, 0).s;
    size_t length = strlen(str);
    
    BruterInt result = br_new_var(context, bruter_value_i(length), NULL);
    
    return result;
}

BR_FUNCTION(_string_compare)
{
    char* str1 = br_arg(context, args, 0).s;
    char* str2 = br_arg(context, args, 1).s;
    
    int cmp_result = strcmp(str1, str2);
    
    BruterInt result = br_new_var(context, bruter_value_i(cmp_result), NULL);
    
    return result;
}

BR_FUNCTION(_string_format) // dynamic string
{
    char* format = br_arg(context, args, 0).s;
    size_t arg_count = br_arg_count(args);
    
    // Calculate the size needed for the formatted string
    size_t size_needed = snprintf(NULL, 0, format, br_arg(context, args, 1).s);
    
    // Allocate memory for the formatted string
    char* result_str = malloc(size_needed + 1);
    if (result_str == NULL) 
    {
        printf("BR_ERROR: Memory allocation failed\n");
        return -1;
    }
    
    // Format the string
    snprintf(result_str, size_needed + 1, format, br_arg(context, args, 1).s);
    
    BruterInt result = br_new_var(context, bruter_value_p(result_str), NULL);

    BruterList *allocs = br_get_allocs(context);
    bruter_push(allocs, bruter_value_p(result_str), NULL);
    
    return result;
}

BR_INIT(string)
{
    br_add_function(context, "string.concat", _string_concat);
    br_add_function(context, "string.length", _string_length);
    br_add_function(context, "string.compare", _string_compare);
    br_add_function(context, "string.format", _string_format);
}
