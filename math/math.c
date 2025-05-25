#include "br.h"

LIST_FUNCTION(_iadd)
{
    ARG(0).i += ARG(1).i;
    return -1;
}

LIST_FUNCTION(_isub)
{
    ARG(0).i -= ARG(1).i;
    return -1;
}

LIST_FUNCTION(_imul)
{
    ARG(0).i *= ARG(1).i;
    return -1;
}

LIST_FUNCTION(_idiv)
{
    ARG(0).i /= ARG(1).i;
    return -1;
}

LIST_FUNCTION(_imod)
{
    ARG(0).i %= ARG(1).i;
    return -1;
}

LIST_FUNCTION(_fadd)
{
    ARG(0).f += ARG(1).f;
    return -1;
}

LIST_FUNCTION(_fsub)
{
    ARG(0).f -= ARG(1).f;
    return -1;
}

LIST_FUNCTION(_fmul)
{
    ARG(0).f *= ARG(1).f;
    return -1;
}

LIST_FUNCTION(_fdiv)
{
    ARG(0).f /= ARG(1).f;
    return -1;
}

LIST_FUNCTION(_fmod)
{
    ARG(0).f = fmod(ARG(0).f, ARG(1).f);
    return -1;
}

INIT(math)
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