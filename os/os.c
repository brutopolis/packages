#include "buxu.h"

function(_read_file)
{
    char *filename = arg_s(0);
    char *content = file_read(filename);
    if (content == NULL)
    {
        buxu_error("failed to read file: %s", filename);
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

function(_write_file)
{
    char *filename = arg_s(0);
    char *content = arg_s(1);
    file_write(filename, content);
    return -1;
}

function(_file_exists)
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