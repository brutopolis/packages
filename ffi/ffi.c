// this is just a simple and easy abstraction over TinyCC
// a proper libtcc wrapper is planned but not any soon


#ifndef ARDUINO

#include "buxu.h"
#include <libtcc.h>

typedef void (*InitFunction)(VirtualMachine*);

List *ffi_state_list;

const char* bruter_header = "#include \"buxu.h\"\n";

void add_common_symbols(TCCState *tcc)
{
    const void *core_funcs[] = {
        str_format,
        special_split,
        make_vm,
        free_vm,
        new_var,
        label_find,
        label_set,
        label_unset,
        eval,
        interpret,
        parse
    };

    const char *core_names[] = {
        "str_format",
        "special_split",
        "make_vm",
        "free_vm",
        "new_var",
        "label_find",
        "label_set",
        "label_unset",
        "eval",
        "interpret",
        "parse"
    };

    for (Int i = 0; i < sizeof(core_funcs) / sizeof(core_funcs[0]); i++) 
    {
        tcc_add_symbol(tcc, core_names[i], core_funcs[i]);
    }
}


function(brl_tcc_clear_states)
{
    while (ffi_state_list->size > 0) 
    {
        tcc_delete((TCCState *)(list_shift(ffi_state_list)).s);
    }
    return -1;
}

function(brl_tcc_c_new_function)
{
    TCCState *tcc = tcc_new();
    if (!tcc) 
    {
        fprintf(stderr, "error initializing TCC\n");
        return -1;
    }

    tcc_set_output_type(tcc, TCC_OUTPUT_MEMORY);

    Int result = new_var(vm, NULL);
    if (result < 0) 
    {
        fprintf(stderr, "could not create new var\n");
        return -1;
    }
    data(result).p = tcc;

    char *code = str_format("%s\n%s", bruter_header, arg_s(0));

    add_common_symbols(tcc);

    if (tcc_compile_string(tcc, code) < 0) 
    {
        fprintf(stderr, "could not compile string\n");
        return -1;
    }

    if (tcc_relocate(tcc) < 0) 
    {
        fprintf(stderr, "could not relocate code\n");
        return -1;
    }

    char *token = code;
    while (*token) 
    {
        token = strstr(token, "function(");
        if (!token)
        {
            break;
        }

        token += 9;
        char *end = strchr(token, ')');
        if (!end)
        {
            break;
        }

        char *symbol = str_nduplicate(token, end - token);

        void *func = tcc_get_symbol(tcc, symbol);
        if (!func) 
        {
            fprintf(stderr, "could not obtain '%s' symbol\n", symbol);
            free(symbol);
            return -1;
        }

        list_push(ffi_state_list, (Value){.p = tcc});

        Int index = new_var(vm, symbol);
        if (index < 0) 
        {
            fprintf(stderr, "could not create new var\n");
            free(symbol);
            return -1;
        }

        data(index).p = func;
        free(symbol);

        token = end + 1;
    }

    free(code);
    return -1;
}

void _terminate_tcc_at_exit_handler()
{
    brl_tcc_clear_states(NULL, NULL);
    list_free(ffi_state_list);
}

init(ffi)
{
    ffi_state_list = list_init(0);

    if (!ffi_state_list) 
    {
        fprintf(stderr, "could not create ffi state list\n");
        return;
    }

    add_function(vm, "ffi.clear", brl_tcc_clear_states);
    add_function(vm, "ffi.compile", brl_tcc_c_new_function);

    atexit(_terminate_tcc_at_exit_handler);
}

#endif