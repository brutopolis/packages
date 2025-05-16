#include "buxu.h"

// file stuff
char* file_read(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return NULL;
    }

    char *code = (char*)malloc(1);
    if (code == NULL)
    {
        printf("BRUTER_ERROR: could not allocate memory for file\n");
        fclose(file);
        return NULL;
    }

    code[0] = '\0';

    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1)
    {
        size_t new_size = strlen(code) + strlen(line) + 1;
        char *temp = realloc(code, new_size);
        if (temp == NULL)
        {
            printf("BRUTER_ERROR: could not reallocate memory while reading file\n");
            free(code);
            free(line);
            fclose(file);
            return NULL;
        }
        code = temp;
        strcat(code, line);
    }

    free(line);
    fclose(file);
    return code;
}

void file_write(char *filename, char *code)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        return;
    }

    fprintf(file, "%s", code);
    fclose(file);
}

bool file_exists(char* filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return false;
    }

    fclose(file);
    return true;
}

list_function(_read_file)
{
    char *filename = arg_s(0);
    char *content = file_read(filename);
    if (content == NULL)
    {
        printf("BRUTER_ERROR: failed to read file: %s\n", filename);
        return -1;
    }

    Int len = strlen(content);
    Int blocks = (len+1) / sizeof(void*);
    Int var = new_block(context, blocks, NULL);
    
    memcpy(&context->data[var].u8[0], content, len);
    ((uint8_t*)context->data)[(var*sizeof(void*)) + len] = '\0';

    free(content);    
    return var;
}

list_function(_write_file)
{
    char *filename = arg_s(0);
    char *content = arg_s(1);
    file_write(filename, content);
    return -1;
}

list_function(_file_exists)
{
    char *filename = arg_s(0);
    return file_exists(filename);
}

init(os)
{
    // register functions
    add_function(context, "file.read", _read_file);
    add_function(context, "file.write", _write_file);
    add_function(context, "file.exists", _file_exists);
}