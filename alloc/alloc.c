#include "br.h"

List *allocs_cache = NULL;
List *allocs_cache_size = NULL;

LIST_FUNCTION(_alloc_new)
{
    Int size = ARG(0).i;
    Int index = new_var(context, NULL);
    DATA(index).p = malloc(size);
    if (DATA(index).p == NULL)
    {
        printf("BRUTER_ERROR: failed to allocate memory for new block\n");
        exit(EXIT_FAILURE);
    }
    list_push(allocs_cache, DATA(index), NULL);
    list_push(allocs_cache_size, VALUE(i, size), NULL);
    return index;
}

LIST_FUNCTION(_alloc_free)
{
    Int found = list_find(allocs_cache, VALUE(p, DATA(ARG(0).i).p), NULL);
    if (found == -1)
    {
        printf("BRUTER_ERROR: invalid pointer for free\n");
        return -1;
    }
    else
    {
        free(list_remove(allocs_cache, found).p);
        list_remove(allocs_cache_size, found);
    }
    return -1;
}

LIST_FUNCTION(_alloc_resize)
{
    Int found = list_find(allocs_cache, VALUE(p, DATA(ARG(0).i).p), NULL);
    if (found == -1)
    {
        printf("BRUTER_ERROR: invalid pointer for resize\n");
        return -1;
    }
    else
    {
        Int new_size = ARG(1).i;
        void *new_ptr = realloc(DATA(ARG(0).i).p, new_size);
        if (new_ptr == NULL)
        {
            printf("BRUTER_ERROR: failed to resize memory block\n");
            return -1;
        }
        DATA(ARG(0).i).p = new_ptr;
        allocs_cache->data[found].p = new_ptr;
        allocs_cache_size->data[found].i = new_size;
    }
    return -1;
}

LIST_FUNCTION(_alloc_concat_string)
{
    Int found = list_find(allocs_cache, VALUE(p, DATA(ARG(0).i).p), NULL);
    if (found == -1)
    {
        printf("BRUTER_ERROR: invalid pointer for concat string\n");
        return -1;
    }
    else
    {
        char *str = (char *)DATA(ARG(0).i).p;
        Int size = allocs_cache_size->data[found].i;
        char *new_str = malloc(size + strlen(ARG(1).s) + 1);
        if (new_str == NULL)
        {
            printf("BRUTER_ERROR: failed to allocate memory for new string\n");
            return -1;
        }
        memcpy(new_str, str, size);
        strcpy(new_str + size, ARG(1).s);
        free(str);
        DATA(ARG(0).i).p = new_str;
        allocs_cache->data[found].p = new_str;
        allocs_cache_size->data[found].i = size + strlen(ARG(1).s) + 1;
    }
    return -1;
}

LIST_FUNCTION(_alloc_concat_byte)
{
    Int found = list_find(allocs_cache, VALUE(p, DATA(ARG(0).i).p), NULL);
    if (found == -1)
    {
        printf("BRUTER_ERROR: invalid pointer for concat byte\n");
        return -1;
    }
    else
    {
        char *str = (char *)DATA(ARG(0).i).p;
        Int size = allocs_cache_size->data[found].i;
        char *new_str = malloc(size + 1);
        if (new_str == NULL)
        {
            printf("BRUTER_ERROR: failed to allocate memory for new byte\n");
            return -1;
        }
        memcpy(new_str, str, size);
        new_str[size] = ARG(1).i;
        free(str);
        DATA(ARG(0).i).p = new_str;
        allocs_cache->data[found].p = new_str;
        allocs_cache_size->data[found].i = size + 1;
    }
    return -1;
}

LIST_FUNCTION(_alloc_concat_int)
{
    Int found = list_find(allocs_cache, VALUE(p, DATA(ARG(0).i).p), NULL);
    if (found == -1)
    {
        printf("BRUTER_ERROR: invalid pointer for concat int\n");
        return -1;
    }
    else
    {
        char *str = (char *)DATA(ARG(0).i).p;
        Int size = allocs_cache_size->data[found].i;
        char *new_str = malloc(size + 20); // 20 is enough for any int
        if (new_str == NULL)
        {
            printf("BRUTER_ERROR: failed to allocate memory for new int\n");
            return -1;
        }
        memcpy(new_str, str, size);
        sprintf(new_str + size, "%d", ARG(1).i);
        free(str);
        DATA(ARG(0).i).p = new_str;
        allocs_cache->data[found].p = new_str;
        allocs_cache_size->data[found].i = size + strlen(new_str + size) + 1;
    }
    return -1;
}

LIST_FUNCTION(_alloc_set_string) // alloc, size, position, string
{ // resize if needed
    Int found = list_find(allocs_cache, VALUE(p, DATA(ARG(0).i).p), NULL);
    if (found == -1)
    {
        printf("BRUTER_ERROR: invalid pointer for set string\n");
        return -1;
    }
    else
    {
        char *str = (char *)DATA(ARG(0).i).p;
        Int size = allocs_cache_size->data[found].i;
        Int position = ARG(2).i;
        if (position < 0 || position >= size)
        {
            printf("BRUTER_ERROR: invalid position for set string\n");
            return -1;
        }
        str[position] = ARG(1).s[0];
    }
    return -1;
}


INIT(alloc)
{
    allocs_cache = list_init(0, false);
    allocs_cache_size = list_init(0, false);
    add_function(context, "alloc.new", _alloc_new);
    add_function(context, "alloc.free", _alloc_free);
}
