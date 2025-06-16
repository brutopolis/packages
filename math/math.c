#include <bruter-representation.h>

// int functions

BR_FUNCTION(_iadd)
{
    br_arg_set(context, args, 0, bruter_value_i(br_arg_get(context, args, 0).i + br_arg_get(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_isub)
{
    br_arg_set(context, args, 0, bruter_value_i(br_arg_get(context, args, 0).i - br_arg_get(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_imul)
{
    br_arg_set(context, args, 0, bruter_value_i(br_arg_get(context, args, 0).i * br_arg_get(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_idiv)
{
    if (br_arg_get(context, args, 1).i == 0)
    {
        printf("BR_ERROR: Division by zero\n");
        return -1; // or handle error appropriately
    }
    br_arg_set(context, args, 0, bruter_value_i(br_arg_get(context, args, 0).i / br_arg_get(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_imod)
{
    if (br_arg_get(context, args, 1).i == 0)
    {
        printf("BR_ERROR: Division by zero\n");
        return -1; // or handle error appropriately
    }
    br_arg_set(context, args, 0, bruter_value_i(br_arg_get(context, args, 0).i % br_arg_get(context, args, 1).i));
    return -1;
}

// float functions

BR_FUNCTION(_fadd)
{
    br_arg_set(context, args, 0, bruter_value_f(br_arg_get(context, args, 0).f + br_arg_get(context, args, 1).f));
    return -1;
}

BR_FUNCTION(_fsub)
{
    br_arg_set(context, args, 0, bruter_value_f(br_arg_get(context, args, 0).f - br_arg_get(context, args, 1).f));
    return -1;
}

BR_FUNCTION(_fmul)
{
    br_arg_set(context, args, 0, bruter_value_f(br_arg_get(context, args, 0).f * br_arg_get(context, args, 1).f));
    return -1;
}

BR_FUNCTION(_fdiv)
{
    if (br_arg_get(context, args, 1).f == 0.0f)
    {
        printf("BR_ERROR: Division by zero\n");
        return -1; // or handle error appropriately
    }
    br_arg_set(context, args, 0, bruter_value_f(br_arg_get(context, args, 0).f / br_arg_get(context, args, 1).f));
    return -1;
}

BR_FUNCTION(_fmod)
{
    br_arg_set(context, args, 0, bruter_value_f(fmod(br_arg_get(context, args, 0).f, br_arg_get(context, args, 1).f)));
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
                    br_arg_set(context, args, 0, bruter_value_i(br_arg_get(context, args, 0).i + br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    br_arg_set(context, args, 0, bruter_value_f(br_arg_get(context, args, 0).i + br_arg_get(context, args, 1).f));
                    break;
                default:
                    printf("BR_ERROR: Unsupported type for addition\n");
            }
            break;
        case BR_TYPE_FLOAT:
            switch (br_arg_get_type(context, args, 1))
            {
                case BR_TYPE_ANY:
                    br_arg_set(context, args, 0, bruter_value_f(br_arg_get(context, args, 0).f + br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    br_arg_set(context, args, 0, bruter_value_f(br_arg_get(context, args, 0).f + br_arg_get(context, args, 1).f));
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
                    br_arg_set(context, args, 0, bruter_value_i(br_arg_get(context, args, 0).i - br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    br_arg_set(context, args, 0, bruter_value_f(br_arg_get(context, args, 0).i - br_arg_get(context, args, 1).f));
                    break;
                default:
                    printf("BR_ERROR: Unsupported type for subtraction\n");
            }
            break;
        case BR_TYPE_FLOAT:
            switch (br_arg_get_type(context, args, 1))
            {
                case BR_TYPE_ANY:
                    br_arg_set(context, args, 0, bruter_value_f(br_arg_get(context, args, 0).f - br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    br_arg_set(context, args, 0, bruter_value_f(br_arg_get(context, args, 0).f - br_arg_get(context, args, 1).f));
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
                    br_arg_set(context, args, 0, bruter_value_i(br_arg_get(context, args, 0).i * br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    br_arg_set(context, args, 0, bruter_value_f(br_arg_get(context, args, 0).i * br_arg_get(context, args, 1).f));
                    break;
                default:
                    printf("BR_ERROR: Unsupported type for multiplication\n");
            }
            break;
        case BR_TYPE_FLOAT:
            switch (br_arg_get_type(context, args, 1))
            {
                case BR_TYPE_ANY:
                    br_arg_set(context, args, 0, bruter_value_f(br_arg_get(context, args, 0).f * br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    br_arg_set(context, args, 0, bruter_value_f(br_arg_get(context, args, 0).f * br_arg_get(context, args, 1).f));
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
                    br_arg_set(context, args, 0, bruter_value_i(br_arg_get(context, args, 0).i / br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    if (br_arg_get(context, args, 1).f == 0.0f)
                    {
                        printf("BR_ERROR: Division by zero\n");
                        return -1; // or handle error appropriately
                    }
                    br_arg_set(context, args, 0, bruter_value_f(br_arg_get(context, args, 0).i / br_arg_get(context, args, 1).f));
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
                    br_arg_set(context, args, 0, bruter_value_f(br_arg_get(context, args, 0).f / br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    if (br_arg_get(context, args, 1).f == 0.0f)
                    {
                        printf("BR_ERROR: Division by zero\n");
                        return -1; // or handle error appropriately
                    }
                    br_arg_set(context, args, 0, bruter_value_f(br_arg_get(context, args, 0).f / br_arg_get(context, args, 1).f));
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
                    br_arg_set(context, args, 0, bruter_value_i(br_arg_get(context, args, 0).i % br_arg_get(context, args, 1).i));
                    break;
                case BR_TYPE_FLOAT:
                    if (br_arg_get(context, args, 1).f == 0.0f)
                    {
                        printf("BR_ERROR: Division by zero\n");
                        return -1; // or handle error appropriately
                    }
                    br_arg_set(context, args, 0, bruter_value_f(fmod(br_arg_get(context, args, 0).i, br_arg_get(context, args, 1).f)));
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
                    br_arg_set(context, args, 0, bruter_value_f(fmod(br_arg_get(context, args, 0).f, br_arg_get(context, args, 1).i)));
                    break;
                case BR_TYPE_FLOAT:
                    if (br_arg_get(context, args, 1).f == 0.0f)
                    {
                        printf("BR_ERROR: Division by zero\n");
                        return -1; // or handle error appropriately
                    }
                    br_arg_set(context, args, 0, bruter_value_f(fmod(br_arg_get(context, args, 0).f, br_arg_get(context, args, 1).f)));
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

BR_INIT(math)
{
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