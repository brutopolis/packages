// this is just a simple and easy abstraction over TinyCC
// a proper libtcc wrapper is planned but not any soon


#ifndef ARDUINO

#include <bruter-representation.h>
#include <libtcc.h>

BruterList *dycc_state_list;

const char* bruter_header = "#include \"bruter-representation.h\"\n";

BR_FUNCTION(brl_tcc_clear_states)
{
    while (dycc_state_list->size > 0) 
    {
        tcc_delete((TCCState *)(bruter_shift(dycc_state_list)).p);
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

    char *code = br_str_format("%s\n%s", bruter_header, br_arg_get(context, args, 0).p);

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

        bruter_push(dycc_state_list, (BruterValue){.p = tcc}, NULL, 0);

        BruterInt index = br_new_var(context, bruter_value_pointer(func), symbol, BR_TYPE_FUNCTION);
        if (index < 0) 
        {
            free(symbol);
            return -1;
        }
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
    dycc_state_list = bruter_new(0, false, false);

    if (!dycc_state_list) 
    {
        fprintf(stderr, "could not create dycc state list\n");
        return;
    }

    bruter_push_pointer(context, brl_tcc_clear_states, "dycc.clear", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, brl_tcc_c_new_function, "dycc.compile", BR_TYPE_FUNCTION);

    atexit(_terminate_tcc_at_exit_handler);
}

#endif