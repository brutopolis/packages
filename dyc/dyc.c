// this is just a simple and easy abstraction over TinyCC
// a proper libtcc wrapper is planned but not any soon


#ifndef ARDUINO

#include "buxu.h"
#include <libtcc.h>

typedef void (*InitFunction)(VirtualMachine*);

List *dyc_state_list;

const char* bruter_header = "#include \"buxu.h\"\n";

void add_common_symbols(TCCState *tcc)
{
    const void *core_funcs[] = {
        str_format,
        special_space_split,
        special_split,
        make_vm,
        free_vm,
        new_var,
        hash_find,
        hash_set,
        hash_unset,
        eval,
        interpret,
        parse
    };

    const char *core_names[] = {
        "str_format",
        "special_space_split",
        "special_split",
        "make_vm",
        "free_vm",
        "new_var",
        "hash_find",
        "hash_set",
        "hash_unset",
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
    while (dyc_state_list->size > 0) 
    {
        tcc_delete((TCCState *)(list_shift(dyc_state_list)).s);
    }
    return -1;
}

function(brl_tcc_c_new_function) // a combo of new_state + compile + relocate + get_symbol
{
    TCCState *tcc = tcc_new();
    if (!tcc) 
    {
        fprintf(stderr, "error initializing TCC\n");
        return -1;
    }

    // Configurar saída para memória
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

    for (Int i = 1; i < args->size; i++) 
    {
        void *func = tcc_get_symbol(tcc, arg_s(i));
        if (!func) 
        {
            fprintf(stderr, "could not obtain '%s' symbol\n", arg_s(i));
            return -1;
        }

        list_push(dyc_state_list, (Value){.p=tcc});

        Int index = new_var(vm, arg_s(i));
        if (index < 0) 
        {
            fprintf(stderr, "could not create new var\n");
            return -1;
        }
        data(index).p = func;
    }
    free(code);
    return -1;
}

void _terminate_tcc_at_exit_handler()
{
    brl_tcc_clear_states(NULL, NULL);
    list_free(dyc_state_list);
}

init(dyc)
{
    dyc_state_list = list_init(0);

    if (!dyc_state_list) 
    {
        fprintf(stderr, "could not create dyc state list\n");
        return;
    }

    add_function(vm, "dycc.clear", brl_tcc_clear_states);
    add_function(vm, "dycc.compile", brl_tcc_c_new_function);

    atexit(_terminate_tcc_at_exit_handler);
}

#endif