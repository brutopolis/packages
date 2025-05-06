// this is just a simple and easy abstraction over TinyCC
// a proper libtcc wrapper is planned but not any soon


#ifndef ARDUINO

#include "buxu.h"
#include <libtcc.h>

List *dycc_state_list;

const char* bruter_header = "#include \"buxu.h\"\n";
typedef void (*InitFunction)(List*);

void add_common_symbols(TCCState *tcc)
{
    const void *core_funcs[] = {
        list_init,
        list_free,
        list_double,
        list_half,
        list_push,
        list_unshift,
        list_insert,
        list_pop,
        list_shift,
        list_remove,
        list_swap,
        list_fast_remove,
        list_find,
        list_reverse,
        list_call,
        list_set,
        file_read,
        file_exists,
        file_write,
        str_duplicate,
        str_nduplicate,
        special_space_split,
        special_split,
        str_format,
        new_var,
        new_block,
        new_string,
        parse_number,
        parse,
        eval
    };

    const char *core_names[] = {
        "list_init",
        "list_free",
        "list_double",
        "list_half",
        "list_push",
        "list_unshift",
        "list_insert",
        "list_pop",
        "list_shift",
        "list_remove",
        "list_swap",
        "list_fast_remove",
        "list_find",
        "list_reverse",
        "list_call",
        "list_set",
        "file_read",
        "file_exists",
        "file_write",
        "str_duplicate",
        "str_nduplicate",
        "special_space_split",
        "special_split",
        "str_format",
        "new_var",
        "new_block",
        "new_string",
        "parse_number",
        "parse",
        "eval"
    };

    for (Int i = 0; i < sizeof(core_funcs) / sizeof(core_funcs[0]); i++) 
    {
        tcc_add_symbol(tcc, core_names[i], core_funcs[i]);
    }
}


function(brl_tcc_clear_states)
{
    while (dycc_state_list->size > 0) 
    {
        tcc_delete((TCCState *)(list_shift(dycc_state_list)).s);
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

    Int result = new_var(context, NULL);
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

        list_push(dycc_state_list, (Value){.p = tcc}, NULL);

        Int index = new_var(context, symbol);
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
    list_free(dycc_state_list);
}

init(dycc)
{
    dycc_state_list = list_init(0, false);

    if (!dycc_state_list) 
    {
        fprintf(stderr, "could not create dycc state list\n");
        return;
    }

    add_function(context, "dycc.clear", brl_tcc_clear_states);
    add_function(context, "dycc.compile", brl_tcc_c_new_function);

    atexit(_terminate_tcc_at_exit_handler);
}

#endif