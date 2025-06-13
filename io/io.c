#include <bruter-representation.h>

BR_FUNCTION(print_int)
{
    printf("%d\n", br_arg(context, args, 0).i);
    return -1;
}

BR_FUNCTION(print_uint)
{
    printf("%u\n", br_arg(context, args, 0).i);
    return -1;
}

BR_FUNCTION(print_float)
{
    printf("%f\n", br_arg(context, args, 0).f);
    return -1;
}

BR_FUNCTION(print_string)
{
    printf("%s\n", br_arg(context, args, 0).s);
    return -1;
}

BR_FUNCTION(print_bool)
{
    printf("%s\n", br_arg(context, args, 0).i ? "true" : "false");
    return -1;
}

BR_FUNCTION(print_pointer)
{
    printf("%p\n", br_arg(context, args, 0).p);
    return -1;
}

BR_FUNCTION(print_bits) // as 0b01010101010101010101010101010101 or 0b1010101010101010101010101010101001010101010101010101010101010101 depending on the size of BruterInt
{
    // print the txt 0b0010101010101...
    BruterInt number = br_arg(context, args, 0).i;
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
    BruterInt number = br_arg(context, args, 0).i;
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
    BruterInt number = br_arg(context, args, 0).i;
    BruterInt size = sizeof(BruterInt);
    for (BruterInt i = 0; i < size; i++) {
        printf("%d ", (number >> (i * 8)) & 0xFF);
    }
    printf("\n");
    return -1;
}

BR_FUNCTION(print_octal) // 0o1234567 or 0o123456789 depending on the size of BruterInt
{
    BruterInt number = br_arg(context, args, 0).i;
    printf("0o%lo\n", number);
    return -1;
}

BR_FUNCTION(print_hex)
{
    BruterInt i = br_arg(context, args, 0).i;
    printf("0x%X\n", i);
    return -1;
}

BR_FUNCTION(print_index)
{
    BruterInt i = br_arg_index(args, 0);
    printf("%d\n", i);
    return -1;
}

BR_FUNCTION(print_list)
{
    BruterList *list = (BruterList *)br_arg(context, args, 0).p;
    if (list->keys != NULL)
    {
        for (BruterInt i = 0; i < list->size; i++)
        {
            if (bruter_get_key(list, i) != NULL)
            {
                printf("[%ld](\"%s\"):\t\t", i, bruter_get_key(list, i));
            }
            else
            {
                printf("[%ld](\"\"):\t\t", i);
            }

            printf(" %ld\n", bruter_get(list, i).i);
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

BR_INIT(io)
{
    br_add_function(context, "print.int", print_int);
    br_add_function(context, "print.uint", print_uint);
    br_add_function(context, "print.float", print_float);
    br_add_function(context, "print.string", print_string);
    br_add_function(context, "print.bool", print_bool);
    br_add_function(context, "print.pointer", print_pointer);
    br_add_function(context, "print.bits", print_bits);
    br_add_function(context, "print.bytes", print_bytearray);
    br_add_function(context, "print.octal", print_octal);
    br_add_function(context, "print.hex", print_hex);
    br_add_function(context, "print.bitarray", print_bitarray);
    br_add_function(context, "print.index", print_index);
    br_add_function(context, "print.list", print_list);
}