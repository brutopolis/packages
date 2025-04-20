#include "buxu.h"

function(_read_file)
{
    char *filename = arg(0).s;
    char *content = readfile(filename);
    if (content == NULL)
    {
        buxu_error("failed to read file: %s", filename);
        return -1;
    }
    Int index = new_first_var(vm, NULL);
    data(index).s = content;
    
    return index;
}

function(_write_file)
{
    char *filename = arg(0).s;
    char *content = arg(1).s;
    writefile(filename, content);
    return -1;
}

function(_file_exists)
{
    char *filename = arg(0).s;
    return file_exists(filename);
}

init(os)
{
    // register functions
    register_function("file.read", _read_file);
    register_function("file.write", _write_file);
    register_function("file.exists", _file_exists);
}