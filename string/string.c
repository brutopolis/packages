#include "buxu.h"

function(_string_set)
{
    Int index = arg(1).i;

    arg(0).s[index] = arg_i(2);

    return -1;
}

function(_string_get)
{
    Int index = arg(1).i;

    return arg(0).s[index];
}

function(_string_concat)
{
    char* str1 = arg(0).s;
    char* str2 = arg(1).s;

    char* result = malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(result, str1);
    strcat(result, str2);

    return result;
}

function(_string_replace)
{
    char* str = arg(0).s;
    char* old = arg(1).s;
    char* new = arg(2).s;

    char* result = malloc(strlen(str) + strlen(new) - strlen(old) + 1);
    char* pos = strstr(str, old);
    if (pos != NULL)
    {
        strncpy(result, str, pos - str);
        result[pos - str] = '\0';
        strcat(result, new);
        strcat(result, pos + strlen(old));
    }
    else
    {
        strcpy(result, str);
    }

    return result;
}

function(_string_find)
{
    char* str = arg(0).s;
    char* substr = arg(1).s;

    char* pos = strstr(str, substr);
    if (pos != NULL)
    {
        return pos - str;
    }
    else
    {
        return -1;
    }
}

function(_string_length)
{
    char* str = arg(0).s;

    return strlen(str);
}

function(_string_compare)
{
    char* str1 = arg(0).s;
    char* str2 = arg(1).s;

    return strcmp(str1, str2);
}

function(_string_push)
{
    arg(0).s = (char*)realloc(arg(0).s, strlen(arg(0).s) + 1);
    arg(0).s[strlen(arg(0).s) + 1] = '\0';
    arg(0).s[strlen(arg(0).s)] = arg_i(1);
}



init(string)
{

}