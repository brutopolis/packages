#include "br.h"

BRUTER_FUNCTION(_iadd)
{
    BR_ARG(0).i += BR_ARG(1).i;
    return -1;
}

BRUTER_FUNCTION(_isub)
{
    BR_ARG(0).i -= BR_ARG(1).i;
    return -1;
}

BRUTER_FUNCTION(_imul)
{
    BR_ARG(0).i *= BR_ARG(1).i;
    return -1;
}

BRUTER_FUNCTION(_idiv)
{
    BR_ARG(0).i /= BR_ARG(1).i;
    return -1;
}

BRUTER_FUNCTION(_imod)
{
    BR_ARG(0).i %= BR_ARG(1).i;
    return -1;
}

BRUTER_FUNCTION(_fadd)
{
    BR_ARG(0).f += BR_ARG(1).f;
    return -1;
}

BRUTER_FUNCTION(_fsub)
{
    BR_ARG(0).f -= BR_ARG(1).f;
    return -1;
}

BRUTER_FUNCTION(_fmul)
{
    BR_ARG(0).f *= BR_ARG(1).f;
    return -1;
}

BRUTER_FUNCTION(_fdiv)
{
    BR_ARG(0).f /= BR_ARG(1).f;
    return -1;
}

BRUTER_FUNCTION(_fmod)
{
    BR_ARG(0).f = fmod(BR_ARG(0).f, BR_ARG(1).f);
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