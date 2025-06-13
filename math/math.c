#include <bruter-representation.h>

BR_FUNCTION(_iadd)
{
    br_arg_set(context, args, 0, bruter_value_i(br_arg(context, args, 0).i + br_arg(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_isub)
{
    br_arg_set(context, args, 0, bruter_value_i(br_arg(context, args, 0).i - br_arg(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_imul)
{
    br_arg_set(context, args, 0, bruter_value_i(br_arg(context, args, 0).i * br_arg(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_idiv)
{
    if (br_arg(context, args, 1).i == 0)
    {
        printf("BR_ERROR: Division by zero\n");
        return -1; // or handle error appropriately
    }
    br_arg_set(context, args, 0, bruter_value_i(br_arg(context, args, 0).i / br_arg(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_imod)
{
    if (br_arg(context, args, 1).i == 0)
    {
        printf("BR_ERROR: Division by zero\n");
        return -1; // or handle error appropriately
    }
    br_arg_set(context, args, 0, bruter_value_i(br_arg(context, args, 0).i % br_arg(context, args, 1).i));
    return -1;
}

BR_FUNCTION(_fadd)
{
    br_arg_set(context, args, 0, bruter_value_f(br_arg(context, args, 0).f + br_arg(context, args, 1).f));
    return -1;
}

BR_FUNCTION(_fsub)
{
    br_arg_set(context, args, 0, bruter_value_f(br_arg(context, args, 0).f - br_arg(context, args, 1).f));
    return -1;
}

BR_FUNCTION(_fmul)
{
    br_arg_set(context, args, 0, bruter_value_f(br_arg(context, args, 0).f * br_arg(context, args, 1).f));
    return -1;
}

BR_FUNCTION(_fdiv)
{
    if (br_arg(context, args, 1).f == 0.0f)
    {
        printf("BR_ERROR: Division by zero\n");
        return -1; // or handle error appropriately
    }
    br_arg_set(context, args, 0, bruter_value_f(br_arg(context, args, 0).f / br_arg(context, args, 1).f));
    return -1;
}

BR_FUNCTION(_fmod)
{
    br_arg_set(context, args, 0, bruter_value_f(fmod(br_arg(context, args, 0).f, br_arg(context, args, 1).f)));
    return -1;
}

BR_INIT(math)
{
    br_add_function(context, "i+", _iadd);
    br_add_function(context, "i-", _isub);
    br_add_function(context, "i*", _imul);
    br_add_function(context, "i/", _idiv);
    br_add_function(context, "i%", _imod);

    br_add_function(context, "f+", _fadd);
    br_add_function(context, "f-", _fsub);
    br_add_function(context, "f*", _fmul);
    br_add_function(context, "f/", _fdiv);
    br_add_function(context, "f%", _fmod);
}