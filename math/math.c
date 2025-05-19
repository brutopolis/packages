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
    ADD_FUNCTION(context, "i+", _iadd);
    ADD_FUNCTION(context, "i-", _isub);
    ADD_FUNCTION(context, "i*", _imul);
    ADD_FUNCTION(context, "i/", _idiv);
    ADD_FUNCTION(context, "i%", _imod);

    ADD_FUNCTION(context, "f+", _fadd);
    ADD_FUNCTION(context, "f-", _fsub);
    ADD_FUNCTION(context, "f*", _fmul);
    ADD_FUNCTION(context, "f/", _fdiv);
    ADD_FUNCTION(context, "f%", _fmod);
}