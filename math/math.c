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
    add_function(context, "iadd", _iadd);
    add_function(context, "isub", _isub);
    add_function(context, "imul", _imul);
    add_function(context, "idiv", _idiv);
    add_function(context, "imod", _imod);

    add_function(context, "fadd", _fadd);
    add_function(context, "fsub", _fsub);
    add_function(context, "fmul", _fmul);
    add_function(context, "fdiv", _fdiv);
    add_function(context, "fmod", _fmod);
}