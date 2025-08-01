#include <bruter-representation.h>

BR_FUNCTION(print_int)
{
    printf("%d\n", br_arg_get(context, args, 0).i);
    return -1;
}

BR_FUNCTION(print_uint)
{
    printf("%u\n", br_arg_get(context, args, 0).i);
    return -1;
}

BR_FUNCTION(print_float)
{
    printf("%f\n", br_arg_get(context, args, 0).f);
    return -1;
}

BR_FUNCTION(print_string)
{
    printf("%s\n", br_arg_get(context, args, 0).p);
    return -1;
}

BR_FUNCTION(print_bool)
{
    printf("%s\n", br_arg_get(context, args, 0).i ? "true" : "false");
    return -1;
}

BR_FUNCTION(print_pointer)
{
    printf("%p\n", br_arg_get(context, args, 0).p);
    return -1;
}

BR_FUNCTION(print_bits) // as 0b01010101010101010101010101010101 or 0b1010101010101010101010101010101001010101010101010101010101010101 depending on the size of BruterInt
{
    // print the txt 0b0010101010101...
    BruterInt number = br_arg_get(context, args, 0).i;
    BruterInt size = sizeof(BruterInt);
    printf("0b");
    for (BruterInt i = size * 8 - 1; i >= 0; i--) {
        printf("%d", (number >> i) & 1);
    }
    printf("\n");
    return -1;
}

BR_FUNCTION(print_bitarray) // 00001111 00001111 00001111 11110000 or 00001111 00001111 00001111 11110000 00001111 00001111 00001111 11110000 depending on the size of BruterInt
{
    BruterInt number = br_arg_get(context, args, 0).i;
    BruterInt size = sizeof(BruterInt);
    for (BruterInt i = size * 8 - 1; i >= 0; i--) {
        printf("%d", (number >> i) & 1);
        if (i % 8 == 0) {
            printf(" ");
        }
    }
    printf("\n");
    return -1;
}

BR_FUNCTION(print_bytearray) // [1, 2, 3, 4] or [1, 2, 3, 4, 5, 6, 7, 8] depending on the size of BruterInt
{
    BruterInt number = br_arg_get(context, args, 0).i;
    BruterInt size = sizeof(BruterInt);
    for (BruterInt i = 0; i < size; i++) {
        printf("%d ", (number >> (i * 8)) & 0xFF);
    }
    printf("\n");
    return -1;
}

BR_FUNCTION(print_octal) // 0o1234567 or 0o123456789 depending on the size of BruterInt
{
    BruterInt number = br_arg_get(context, args, 0).i;
    printf("0o%lo\n", number);
    return -1;
}

BR_FUNCTION(print_hex)
{
    BruterInt i = br_arg_get(context, args, 0).i;
    printf("0x%X\n", i);
    return -1;
}

BR_FUNCTION(print_index)
{
    BruterInt i = br_arg_get_index(args, 0);
    printf("%d\n", i);
    return -1;
}

BR_FUNCTION(print_list)
{
    BruterList *list = (BruterList *)br_arg_get(context, args, 0).p;
    if (list->keys != NULL && list->types != NULL)
    {
        for (BruterInt i = 0; i < list->size; i++)
        {
            printf("[%ld]{%s}(%d):\t %ld\n", i, list->keys[i] ? list->keys[i] : "NULL", list->types[i], bruter_get(list, i).i);
        }
    }
    else if (list->keys != NULL)
    {
        for (BruterInt i = 0; i < list->size; i++)
        {
            printf("[%ld]{%s}: %ld\t\t \n", i, list->keys[i] ? list->keys[i] : "NULL", bruter_get(list, i).i);
        }
    }
    else if (list->types != NULL)
    {
        for (BruterInt i = 0; i < list->size; i++)
        {
            printf("[%ld](%d):\t\t %ld\n", i, list->types[i], bruter_get(list, i).i);
        }
    }
    else
    {
        for (BruterInt i = 0; i < list->size; i++)
        {
            printf("[%ld]:\t\t %ld\n", i, bruter_get(list, i).i);
        }
    }
    return -1;
}

BR_FUNCTION(io_print)
{
    BruterList *temp_args = NULL;
    for (BruterInt i = 0; i < br_arg_get_count(args); i++)
    {
        int8_t arg_type = br_arg_get_type(context, args, i);
        switch (arg_type)
        {
            case BR_TYPE_FLOAT:
                printf("%f\n", br_arg_get(context, args, i).f);
                break;
            case BR_TYPE_BUFFER:
                printf("%s\n", br_arg_get(context, args, i).p);
                break;
            case BR_TYPE_FUNCTION:
                printf("%p\n", br_arg_get(context, args, i).p);
                break;
            case BR_TYPE_LIST:
            case BR_TYPE_BAKED:
                if (temp_args == NULL)
                {
                    temp_args = bruter_new(0, false, true);
                    bruter_push(temp_args, bruter_value_int(-1), NULL, BR_TYPE_NULL); // dummy value
                }
                bruter_push(temp_args, args->data[i+1], NULL, 0);
                print_list(context, temp_args);
                bruter_pop(temp_args); // remove the list index
                break;
            case BR_TYPE_ANY:
            default:
                printf("%ld\n", br_arg_get(context, args, i).i);
                break;
        }
    }
    if (temp_args != NULL)
    {
        bruter_free(temp_args);
    }
    return -1;
}

BR_INIT(io)
{
    bruter_push_pointer(context, print_int, "print.int", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, print_uint, "print.uint", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, print_float, "print.float", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, print_string, "print.string", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, print_bool, "print.bool", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, print_pointer, "print.pointer", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, print_bits, "print.bits", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, print_bytearray, "print.bytes", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, print_octal, "print.octal", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, print_hex, "print.hex", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, print_bitarray, "print.bitarray", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, print_index, "print.index", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, print_list, "print.list", BR_TYPE_FUNCTION);
    bruter_push_pointer(context, io_print, "print", BR_TYPE_FUNCTION); // auto print
}