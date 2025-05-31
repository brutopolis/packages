// this is just a simple and easy abstraction over TinyCC
// a proper libtcc wrapper is planned but not any soon


#ifndef ARDUINO

#include "bruter-representation.h"
#include <libtcc.h>

BruterList *dycc_state_list;

const char* bruter_header = "#include \"bruter-representation.h\"\n";

void add_common_symbols(TCCState *tcc)
{
    const void *core_funcs[] = {
        br_str_duplicate,
        br_str_nduplicate,
        br_str_space_split,
        br_str_split,
        br_str_format,

        br_new_var,
        br_parser_number,
        br_parse,

        br_eval
    };

    const char *core_names[] = {
        "br_str_duplicate",
        "br_str_nduplicate",
        "br_str_space_split",
        "br_str_split",
        "br_str_format",

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


BR_FUNCTION(brl_tcc_clear_states)
{
    while (dycc_state_list->size > 0) 
    {
        tcc_delete((TCCState *)(bruter_shift(dycc_state_list)).s);
    }
    return -1;
}

BR_FUNCTION(brl_tcc_c_new_function)
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
    bruter_set(context, result, bruter_value_p(tcc));

    char *code = br_str_format("%s\n%s", bruter_header, br_arg(context, args, 0).s);

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
        token = strstr(token, "BR_FUNCTION(");
        if (!token)
        {
            break;
        }

        token += 12;
        char *end = strchr(token, ')');
        if (!end)
        {
            break;
        }

        char *symbol = br_str_nduplicate(token, end - token);

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

        bruter_set(context, index, bruter_value_p(func));
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