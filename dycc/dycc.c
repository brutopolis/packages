// this is just a simple and easy abstraction over TinyCC
// a proper libtcc wrapper is planned but not any soon


#ifndef ARDUINO

#include "br.h"
#include <libtcc.h>

BruterList *dycc_state_list;

const char* bruter_header = "#include \"br.h\"\n";

void add_common_symbols(TCCState *tcc)
{
    const void *core_funcs[] = {
        bruter_init,
        bruter_free,
        bruter_double,
        bruter_half,
        bruter_push,
        bruter_unshift,
        bruter_insert,
        bruter_pop,
        bruter_shift,
        bruter_remove,
        bruter_swap,
        bruter_fast_remove,
        bruter_find,
        bruter_reverse,
        bruter_call,

        str_duplicate,
        str_nduplicate,
        str_space_split,
        str_split,
        str_format,

        br_new_var,
        br_parser_number,
        br_parse,

        br_eval
    };

    const char *core_names[] = {
        "bruter_init",
        "bruter_free",
        "bruter_double",
        "bruter_half",
        "bruter_push",
        "bruter_unshift",
        "bruter_insert",
        "bruter_pop",
        "bruter_shift",
        "bruter_remove",
        "bruter_swap",
        "bruter_fast_remove",
        "bruter_find",
        "bruter_reverse",
        "bruter_call",

        "str_duplicate",
        "str_nduplicate",
        "str_space_split",
        "str_split",
        "str_format",

        "br_new_var",
        "br_parser_number",
        "parse",
        "eval"
    };

    for (BruterInt i = 0; i < sizeof(core_funcs) / sizeof(core_funcs[0]); i++) 
    {
        tcc_add_symbol(tcc, core_names[i], core_funcs[i]);
    }
}


BRUTER_FUNCTION(brl_tcc_clear_states)
{
    while (dycc_state_list->size > 0) 
    {
        tcc_delete((TCCState *)(bruter_shift(dycc_state_list)).s);
    }
    return -1;
}

BRUTER_FUNCTION(brl_tcc_c_new_function)
{
    TCCState *tcc = tcc_new();
    if (!tcc) 
    {
        fprintf(stderr, "error initializing TCC\n");
        return -1;
    }

    tcc_set_output_type(tcc, TCC_OUTPUT_MEMORY);

    BruterInt result = br_new_var(context, NULL);
    if (result < 0) 
    {
        fprintf(stderr, "could not create new var\n");
        return -1;
    }
    BR_DATA(result).p = tcc;

    char *code = str_format("%s\n%s", bruter_header, BR_ARG(0).s);

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

        bruter_push(dycc_state_list, (BruterValue){.p = tcc}, NULL);

        BruterInt index = br_new_var(context, symbol);
        if (index < 0) 
        {
            fprintf(stderr, "could not create new var\n");
            free(symbol);
            return -1;
        }

        BR_DATA(index).p = func;
        free(symbol);

        token = end + 1;
    }

    free(code);
    return -1;
}

void _terminate_tcc_at_exit_handler()
{
    brl_tcc_clear_states(NULL, NULL);
    bruter_free(dycc_state_list);
}

BR_INIT(dycc)
{
    dycc_state_list = bruter_init(0, false);

    if (!dycc_state_list) 
    {
        fprintf(stderr, "could not create dycc state list\n");
        return;
    }

    br_add_function(context, "dycc.clear", brl_tcc_clear_states);
    br_add_function(context, "dycc.compile", brl_tcc_c_new_function);

    atexit(_terminate_tcc_at_exit_handler);
}

#endif