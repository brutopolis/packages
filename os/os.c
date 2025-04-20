#include "buxu.h"

function(_read_file)
{
    char *filename = &arg(0).u8[0];
    char *content = readfile(filename);
    if (content == NULL)
    {
        buxu_error("failed to read file: %s", filename);
        return -1;
    }

    Int len = strlen(content);
    Int blocks = (len+1) / sizeof(void*);
    Int var = new_block(vm, NULL, blocks);
    
    memcpy(&vm->values->data[var].u8[0], content, len);
    ((uint8_t*)vm->values->data)[(var*sizeof(void*)) + len] = '\0';

    free(content);    
    return var;
}

function(_write_file)
{
    char *filename = &arg(0).u8[0];
    char *content = &arg(1).u8[0];
    writefile(filename, content);
    return -1;
}

function(_file_exists)
{
    char *filename = &arg(0).u8[0];
    return file_exists(filename);
}

init(os)
{
    // register functions
    register_function("file.read", _read_file);
    register_function("file.write", _write_file);
    register_function("file.exists", _file_exists);
}