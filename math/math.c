#include "buxu.h"

list_function(_iadd)
{
    arg(0).i += arg(1).i;
    return -1;
}

list_function(_isub)
{
    arg(0).i -= arg(1).i;
    return -1;
}

list_function(_imul)
{
    arg(0).i *= arg(1).i;
    return -1;
}

list_function(_idiv)
{
    arg(0).i /= arg(1).i;
    return -1;
}

list_function(_imod)
{
    arg(0).i %= arg(1).i;
    return -1;
}

list_function(_fadd)
{
    arg(0).f += arg(1).f;
    return -1;
}

list_function(_fsub)
{
    arg(0).f -= arg(1).f;
    return -1;
}

list_function(_fmul)
{
    arg(0).f *= arg(1).f;
    return -1;
}

list_function(_fdiv)
{
    arg(0).f /= arg(1).f;
    return -1;
}

list_function(_fmod)
{
    arg(0).f = fmod(arg(0).f, arg(1).f);
    return -1;
}

init(math)
{
    add_function(context, "i+", _iadd);
    add_function(context, "i-", _isub);
    add_function(context, "i*", _imul);
    add_function(context, "i/", _idiv);
    add_function(context, "i%", _imod);

    add_function(context, "f+", _fadd);
    add_function(context, "f-", _fsub);
    add_function(context, "f*", _fmul);
    add_function(context, "f/", _fdiv);
    add_function(context, "f%", _fmod);
}