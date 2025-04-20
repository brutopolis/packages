#include "buxu.h"

function(print_int)
{
    printf("%d\n", arg(0).i);
}

function(print_float)
{
    printf("%f\n", arg(0).f);
}

function(print_string)
{
    printf("%s\n", arg(0).s);
}

function(print_bool)
{
    printf("%s\n", arg(0).i ? "true" : "false");
}

function(print_pointer)
{
    printf("%p\n", arg(0).p);
}

function(format)
{
    char *_format = arg(0).s;
    char *result = malloc(strlen(_format) + 1);
    for (int i = 0; _format[i] != '\0'; i++) 
    {
        if (_format[i] == '%') {
            if (_format[i + 1] == 'd') 
            {
                sprintf(result, "%d", arg(1).i);
                i++;
            } 
            else if (_format[i + 1] == 'f') 
            {
                sprintf(result, "%f", arg(1).f);
                i++;
            } 
            else if (_format[i + 1] == 's') 
            {
                sprintf(result, "%s", arg(1).s);
                i++;
            } 
            else if (_format[i + 1] == 'b') 
            {
                sprintf(result, "%s", arg(1).i ? "true" : "false");
                i++;
            }
        } else {
            result[i] = _format[i];
        }
    }
    result[strlen(_format)] = '\0';

    Int index = new_first_var(vm, NULL);
    vm->values->data[index].s = result;
    return index;
}

init(io)
{
    add_function(vm, "print.int", print_int);
    add_function(vm, "print.float", print_float);
    add_function(vm, "print.string", print_string);
    add_function(vm, "print.bool", print_bool);
    add_function(vm, "print.pointer", print_pointer);
    add_function(vm, "format", format);
}