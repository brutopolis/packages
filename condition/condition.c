#include "rawer.h"

function(rawer_condition_equals)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a == b ? 1 : 0, NULL, BR_TYPE_ANY);
}

function(rawer_condition_not_equals)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a != b ? 1 : 0, NULL, BR_TYPE_ANY);
}

function(rawer_condition_greater_than)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a > b ? 1 : 0, NULL, BR_TYPE_ANY);
}

function(rawer_condition_less_than)
{
    BruterInt a = bruter_pop_int(stack);
    BruterInt b = bruter_pop_int(stack);
    bruter_push_int(stack, a < b ? 1 : 0, NULL, BR_TYPE_ANY);
}

init(condition)
{
    bruter_push_pointer(context, rawer_condition_equals, "equals", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_condition_not_equals, "not_equals", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_condition_greater_than, "greater", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, rawer_condition_less_than, "less", BR_TYPE_FUNCTION);
}