#include <bruter-representation.h>

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
        printf("BR_ERROR: could not allocate memory for file\n");
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
            printf("BR_ERROR: could not reallocate memory while reading file\n");
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

BR_FUNCTION(_read_file)
{
    char *filename = br_arg(context, args, 0).s;
    char *content = file_read(filename);
    
    if (content == NULL)
    {
        printf("BR_ERROR: could not read file '%s'\n", filename);
        return -1; // return an error code
    }
    BruterInt var = br_new_var(context, bruter_value_p(content), NULL, BR_TYPE_STRING);

    free(content);    
    return var;
}

BR_FUNCTION(_write_file)
{
    char *filename = br_arg(context, args, 0).s;
    char *content = br_arg(context, args, 1).s;
    file_write(filename, content);
    return -1;
}

BR_FUNCTION(_file_exists)
{
    char *filename = br_arg(context, args, 0).s;
    return file_exists(filename);
}

BR_INIT(os)
{
    // register functions
    br_add_function(context, "file.read", _read_file);
    br_add_function(context, "file.write", _write_file);
    br_add_function(context, "file.exists", _file_exists);
}