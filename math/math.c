#include "buxu.h"

function(_iadd)
{
    arg(0).i += arg(1).i;
    return -1;
}

function(_isub)
{
    arg(0).i -= arg(1).i;
    return -1;
}

function(_imul)
{
    arg(0).i *= arg(1).i;
    return -1;
}

function(_idiv)
{
    arg(0).i /= arg(1).i;
    return -1;
}

function(_imod)
{
    arg(0).i %= arg(1).i;
    return -1;
}

function(_fadd)
{
    arg(0).f += arg(1).f;
    return -1;
}

function(_fsub)
{
    arg(0).f -= arg(1).f;
    return -1;
}

function(_fmul)
{
    arg(0).f *= arg(1).f;
    return -1;
}

function(_fdiv)
{
    arg(0).f /= arg(1).f;
    return -1;
}

function(_fmod)
{
    arg(0).f = fmod(arg(0).f, arg(1).f);
    return -1;
}

init(math)
{
    add_function(vm, "iadd", _iadd);
    add_function(vm, "isub", _isub);
    add_function(vm, "imul", _imul);
    add_function(vm, "idiv", _idiv);
    add_function(vm, "imod", _imod);

    add_function(vm, "fadd", _fadd);
    add_function(vm, "fsub", _fsub);
    add_function(vm, "fmul", _fmul);
    add_function(vm, "fdiv", _fdiv);
    add_function(vm, "fmod", _fmod);
}