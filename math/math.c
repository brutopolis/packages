#include <bruter-representation.h>

// int functions

BR_FUNCTION(_iadd)
{
    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i + br_arg_get(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_isub)
{
    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i - br_arg_get(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_imul)
{
    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i * br_arg_get(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_idiv)
{
    if (br_arg_get(context, args, 1).i == 0)
    {
        printf("BR_ERROR: Division by zero\n");
        return -1; // or handle error appropriately
    }
    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i / br_arg_get(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_imod)
{
    if (br_arg_get(context, args, 1).i == 0)
    {
        printf("BR_ERROR: Division by zero\n");
        return -1; // or handle error appropriately
    }
    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i % br_arg_get(context, args, 1).i));
    return -1;
}

// float functions

BR_FUNCTION(_fadd)
{
    br_arg_set(context, args, 0, bruter_value_float(br_arg_get(context, args, 0).f + br_arg_get(context, args, 1).f));
    return -1;
}

BR_FUNCTION(_fsub)
{
    br_arg_set(context, args, 0, bruter_value_float(br_arg_get(context, args, 0).f - br_arg_get(context, args, 1).f));
    return -1;
}

BR_FUNCTION(_fmul)
{
    br_arg_set(context, args, 0, bruter_value_float(br_arg_get(context, args, 0).f * br_arg_get(context, args, 1).f));
    return -1;
}

BR_FUNCTION(_fdiv)
{
    if (br_arg_get(context, args, 1).f == 0.0f)
    {
        printf("BR_ERROR: Division by zero\n");
        return -1; // or handle error appropriately
    }
    br_arg_set(context, args, 0, bruter_value_float(br_arg_get(context, args, 0).f / br_arg_get(context, args, 1).f));
    return -1;
}

BR_FUNCTION(_fmod)
{
    br_arg_set(context, args, 0, bruter_value_float(fmod(br_arg_get(context, args, 0).f, br_arg_get(context, args, 1).f)));
    return -1;
}

// auto

BR_FUNCTION(_aadd)
{
    switch (br_arg_get_type(context, args, 0))
    {
        case BR_TYPE_ANY:
            switch (br_arg_get_type(context, args, 1))
            {
                case BR_TYPE_ANY:
                    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i + br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    br_arg_set(context, args, 0, bruter_value_float(br_arg_get(context, args, 0).i + br_arg_get(context, args, 1).f));
                    break;
                default:
                    printf("BR_ERROR: Unsupported type for addition\n");
            }
            break;
        case BR_TYPE_FLOAT:
            switch (br_arg_get_type(context, args, 1))
            {
                case BR_TYPE_ANY:
                    br_arg_set(context, args, 0, bruter_value_float(br_arg_get(context, args, 0).f + br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    br_arg_set(context, args, 0, bruter_value_float(br_arg_get(context, args, 0).f + br_arg_get(context, args, 1).f));
                    break;
                default:
                    printf("BR_ERROR: Unsupported type for addition\n");
            }
            break;
        default:
            printf("BR_ERROR: autoadd could not determine type for operation\n");
            return -1;
    }
    return -1;
}

BR_FUNCTION(_asub)
{
    switch (br_arg_get_type(context, args, 0))
    {
        case BR_TYPE_ANY:
            switch (br_arg_get_type(context, args, 1))
            {
                case BR_TYPE_ANY:
                    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i - br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    br_arg_set(context, args, 0, bruter_value_float(br_arg_get(context, args, 0).i - br_arg_get(context, args, 1).f));
                    break;
                default:
                    printf("BR_ERROR: Unsupported type for subtraction\n");
            }
            break;
        case BR_TYPE_FLOAT:
            switch (br_arg_get_type(context, args, 1))
            {
                case BR_TYPE_ANY:
                    br_arg_set(context, args, 0, bruter_value_float(br_arg_get(context, args, 0).f - br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    br_arg_set(context, args, 0, bruter_value_float(br_arg_get(context, args, 0).f - br_arg_get(context, args, 1).f));
                    break;
                default:
                    printf("BR_ERROR: Unsupported type for subtraction\n");
            }
            break;
        default:
            printf("BR_ERROR: autosub could not determine type for operation\n");
            return -1;
    }
    return -1;
}

BR_FUNCTION(_amul)
{
    switch (br_arg_get_type(context, args, 0))
    {
        case BR_TYPE_ANY:
            switch (br_arg_get_type(context, args, 1))
            {
                case BR_TYPE_ANY:
                    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i * br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    br_arg_set(context, args, 0, bruter_value_float(br_arg_get(context, args, 0).i * br_arg_get(context, args, 1).f));
                    break;
                default:
                    printf("BR_ERROR: Unsupported type for multiplication\n");
            }
            break;
        case BR_TYPE_FLOAT:
            switch (br_arg_get_type(context, args, 1))
            {
                case BR_TYPE_ANY:
                    br_arg_set(context, args, 0, bruter_value_float(br_arg_get(context, args, 0).f * br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    br_arg_set(context, args, 0, bruter_value_float(br_arg_get(context, args, 0).f * br_arg_get(context, args, 1).f));
                    break;
                default:
                    printf("BR_ERROR: Unsupported type for multiplication\n");
            }
            break;
        default:
            printf("BR_ERROR: automul could not determine type for operation\n");
            return -1;
    }
    return -1;
}

BR_FUNCTION(_adiv)
{
    switch (br_arg_get_type(context, args, 0))
    {
        case BR_TYPE_ANY:
            switch (br_arg_get_type(context, args, 1))
            {
                case BR_TYPE_ANY:
                    if (br_arg_get(context, args, 1).i == 0)
                    {
                        printf("BR_ERROR: Division by zero\n");
                        return -1; // or handle error appropriately
                    }
                    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i / br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    if (br_arg_get(context, args, 1).f == 0.0f)
                    {
                        printf("BR_ERROR: Division by zero\n");
                        return -1; // or handle error appropriately
                    }
                    br_arg_set(context, args, 0, bruter_value_float(br_arg_get(context, args, 0).i / br_arg_get(context, args, 1).f));
                    break;
                default:
                    printf("BR_ERROR: Unsupported type for division\n");
            }
            break;
        case BR_TYPE_FLOAT:
            switch (br_arg_get_type(context, args, 1))
            {
                case BR_TYPE_ANY:
                    if (br_arg_get(context, args, 1).i == 0)
                    {
                        printf("BR_ERROR: Division by zero\n");
                        return -1; // or handle error appropriately
                    }
                    br_arg_set(context, args, 0, bruter_value_float(br_arg_get(context, args, 0).f / br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    if (br_arg_get(context, args, 1).f == 0.0f)
                    {
                        printf("BR_ERROR: Division by zero\n");
                        return -1; // or handle error appropriately
                    }
                    br_arg_set(context, args, 0, bruter_value_float(br_arg_get(context, args, 0).f / br_arg_get(context, args, 1).f));
                    break;
                default:
                    printf("BR_ERROR: Unsupported type for division\n");
            }
            break;
        default:
            printf("BR_ERROR: autodiv could not determine type for operation\n");
            return -1;
    }
    return -1;
}

BR_FUNCTION(_amod)
{
    switch (br_arg_get_type(context, args, 0))
    {
        case BR_TYPE_ANY:
            switch (br_arg_get_type(context, args, 1))
            {
                case BR_TYPE_ANY:
                    if (br_arg_get(context, args, 1).i == 0)
                    {
                        printf("BR_ERROR: Division by zero\n");
                        return -1; // or handle error appropriately
                    }
                    br_arg_set(context, args, 0, bruter_value_int(br_arg_get(context, args, 0).i % br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    if (br_arg_get(context, args, 1).f == 0.0f)
                    {
                        printf("BR_ERROR: Division by zero\n");
                        return -1; // or handle error appropriately
                    }
                    br_arg_set(context, args, 0, bruter_value_float(fmod(br_arg_get(context, args, 0).i, br_arg_get(context, args, 1).f)));
                    break;
                default:
                    printf("BR_ERROR: Unsupported type for modulo\n");
            }
            break;
        case BR_TYPE_FLOAT:
            switch (br_arg_get_type(context, args, 1))
            {
                case BR_TYPE_ANY:
                    if (br_arg_get(context, args, 1).i == 0)
                    {
                        printf("BR_ERROR: Division by zero\n");
                        return -1; // or handle error appropriately
                    }
                    br_arg_set(context, args, 0, bruter_value_float(fmod(br_arg_get(context, args, 0).f, br_arg_get(context, args, 1).i)));
                    break;
                case BR_TYPE_FLOAT:
                    if (br_arg_get(context, args, 1).f == 0.0f)
                    {
                        printf("BR_ERROR: Division by zero\n");
                        return -1; // or handle error appropriately
                    }
                    br_arg_set(context, args, 0, bruter_value_float(fmod(br_arg_get(context, args, 0).f, br_arg_get(context, args, 1).f)));
                    break;
                default:
                    printf("BR_ERROR: Unsupported type for modulo\n");
            }
            break;
        default:
            printf("BR_ERROR: automod could not determine type for operation\n");
            return -1;
    }
    return -1;
}
// math parser

#define INSERT_OP(opchar) \
if (strncmp(current_word, opchar, strlen(opchar)) == 0 && current_word[strlen(opchar)] == '\0') { \
    if (result->size < 1 || word_index + 1 >= splited_command->size) { \
        printf("BR_ERROR: math parser requires at least 1 result and 1 more word to operate\n"); \
        return false; \
    } \
    bruter_insert(splited_command, word_index + 2, (BruterValue){.p = br_str_duplicate("&" opchar)}, NULL, 0); \
    return true; \
}

#define HANDLE_REAL_OP(sym, op) \
else if (strcmp(current_word, "&" sym) == 0) { \
    BruterInt second_index = bruter_pop_int(result); \
    BruterInt first_index = bruter_pop_int(result); \
    BruterInt index = br_new_var(context, (BruterValue){.i = 0}, NULL, BR_TYPE_ANY); \
    bruter_push_int(result, index, NULL, 0); \
    switch (bruter_get_type(context, first_index)) { \
        case BR_TYPE_FLOAT: \
            switch (bruter_get_type(context, second_index)) { \
                case BR_TYPE_FLOAT: \
                    context->data[index].f = bruter_get_float(context, first_index) op bruter_get_float(context, second_index); \
                    context->types[index] = BR_TYPE_FLOAT; \
                    break; \
                default: \
                    context->data[index].f = bruter_get_float(context, first_index) op (float)bruter_get_int(context, second_index); \
                    context->types[index] = BR_TYPE_FLOAT; \
                    break; \
            } \
            break; \
        default: \
            switch (bruter_get_type(context, second_index)) { \
                case BR_TYPE_FLOAT: \
                    context->data[index].f = (float)bruter_get_int(context, first_index) op bruter_get_float(context, second_index); \
                    context->types[index] = BR_TYPE_FLOAT; \
                    break; \
                default: \
                    context->data[index].i = bruter_get_int(context, first_index) op bruter_get_int(context, second_index); \
                    context->types[index] = BR_TYPE_ANY; \
                    break; \
            } \
            break; \
    } \
    return true; \
}

#define HANDLE_INT_OP(sym, op) \
else if (strcmp(current_word, "&" sym) == 0) { \
    BruterInt second_index = bruter_pop_int(result); \
    BruterInt first_index = bruter_pop_int(result); \
    BruterInt index = br_new_var(context, (BruterValue){.i = 0}, NULL, BR_TYPE_ANY); \
    bruter_push_int(result, index, NULL, 0); \
    if (bruter_get_type(context, first_index) == BR_TYPE_FLOAT || bruter_get_type(context, second_index) == BR_TYPE_FLOAT) { \
        printf("BR_ERROR: %s only supports integer operands\n", sym); \
        return true; \
    } \
    context->data[index].i = bruter_get_int(context, first_index) op bruter_get_int(context, second_index); \
    context->types[index] = BR_TYPE_ANY; \
    return true; \
}

#define HANDLE_COMPOUND_OP(sym, op) \
else if (strcmp(current_word, "&" sym "=") == 0) { \
    BruterInt second_index = bruter_pop_int(result); \
    BruterInt first_index = bruter_pop_int(result); \
    switch (bruter_get_type(context, first_index)) { \
        case BR_TYPE_FLOAT: \
            switch (bruter_get_type(context, second_index)) { \
                case BR_TYPE_FLOAT: \
                    context->data[first_index].f = context->data[first_index].f op bruter_get_float(context, second_index); \
                    break; \
                default: \
                    context->data[first_index].f = context->data[first_index].f op (float)bruter_get_int(context, second_index); \
                    break; \
            } \
            context->types[first_index] = BR_TYPE_FLOAT; \
            break; \
        default: \
            switch (bruter_get_type(context, second_index)) { \
                case BR_TYPE_FLOAT: \
                    context->data[first_index].f = (float)bruter_get_int(context, first_index) op bruter_get_float(context, second_index); \
                    context->types[first_index] = BR_TYPE_FLOAT; \
                    break; \
                default: \
                    context->data[first_index].i = context->data[first_index].i op bruter_get_int(context, second_index); \
                    context->types[first_index] = BR_TYPE_ANY; \
                    break; \
            } \
            break; \
    } \
    bruter_push_int(result, first_index, NULL, 0); \
    return true; \
}

#define HANDLE_INT_COMPOUND_OP(sym, op) \
else if (strcmp(current_word, "&" sym "=") == 0) { \
    BruterInt second_index = bruter_pop_int(result); \
    BruterInt first_index = bruter_pop_int(result); \
    if (bruter_get_type(context, first_index) == BR_TYPE_FLOAT || bruter_get_type(context, second_index) == BR_TYPE_FLOAT) { \
        printf("BR_ERROR: %s= only supports integer operands\n", sym); \
        return true; \
    } \
    context->data[first_index].i = context->data[first_index].i op bruter_get_int(context, second_index); \
    context->types[first_index] = BR_TYPE_ANY; \
    bruter_push_int(result, first_index, NULL, 0); \
    return true; \
}

BR_PARSER_STEP(parser_math)
{
    BR_PARSER_STEP_BASICS();
   
    INSERT_OP("+")
    else INSERT_OP("-")
    else INSERT_OP("*")
    else INSERT_OP("/")
    else INSERT_OP("%")
    else INSERT_OP("&")
    else INSERT_OP("|")
    else INSERT_OP("^")
    else INSERT_OP("<<")
    else INSERT_OP(">>")
    else INSERT_OP("+=")
    else INSERT_OP("-=")
    else INSERT_OP("*=")
    else INSERT_OP("/=")
    else INSERT_OP("%=")
    else INSERT_OP("&=")
    else INSERT_OP("|=")
    else INSERT_OP("^=")
    else INSERT_OP("<<=")
    else INSERT_OP(">>=")


    HANDLE_REAL_OP("+", +)
    HANDLE_REAL_OP("-", -)
    HANDLE_REAL_OP("*", *)
    HANDLE_REAL_OP("/", /)
    HANDLE_INT_OP("%", %)
    HANDLE_INT_OP("&", &)
    HANDLE_INT_OP("|", |)
    HANDLE_INT_OP("^", ^)
    HANDLE_INT_OP("<<", <<)
    HANDLE_INT_OP(">>", >>)

    HANDLE_COMPOUND_OP("+", +)
    HANDLE_COMPOUND_OP("-", -)
    HANDLE_COMPOUND_OP("*", *)
    HANDLE_COMPOUND_OP("/", /)
    HANDLE_INT_COMPOUND_OP("%", %)
    HANDLE_INT_COMPOUND_OP("&", &)
    HANDLE_INT_COMPOUND_OP("|", |)
    HANDLE_INT_COMPOUND_OP("^", ^)
    HANDLE_INT_COMPOUND_OP("<<", <<)
    HANDLE_INT_COMPOUND_OP(">>", >>)

    return false;
}

BR_INIT(math)
{
    // register the math parser
    BruterList *parser = br_get_parser(context);

    // math parser must be before the last step(variable)
    bruter_insert(parser, parser->size - 1, (BruterValue){.p = parser_math}, "math", 0);

    // int
    br_add_function(context, "i+", _iadd);
    br_add_function(context, "i-", _isub);
    br_add_function(context, "i*", _imul);
    br_add_function(context, "i/", _idiv);
    br_add_function(context, "i%", _imod);

    // float
    br_add_function(context, "f+", _fadd);
    br_add_function(context, "f-", _fsub);
    br_add_function(context, "f*", _fmul);
    br_add_function(context, "f/", _fdiv);
    br_add_function(context, "f%", _fmod);

    // auto 
    br_add_function(context, "a+", _aadd);
    br_add_function(context, "a-", _asub);
    br_add_function(context, "a*", _amul);
    br_add_function(context, "a/", _adiv);
    br_add_function(context, "a%", _amod);
}