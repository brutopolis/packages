#include "br.h"

LIST_FUNCTION(print_int)
{
    printf("%d\n", ARG(0).i);
    return -1;
}

LIST_FUNCTION(print_uint)
{
    printf("%u\n", ARG(0).i);
    return -1;
}

LIST_FUNCTION(print_float)
{
    printf("%f\n", ARG(0).f);
    return -1;
}

LIST_FUNCTION(print_string)
{
    printf("%s\n", ARG_S(0));
    return -1;
}

LIST_FUNCTION(print_bool)
{
    printf("%s\n", ARG(0).i ? "true" : "false");
    return -1;
}

LIST_FUNCTION(print_pointer)
{
    printf("%p\n", ARG(0).p);
    return -1;
}

LIST_FUNCTION(print_bits) // as 0b01010101010101010101010101010101 or 0b1010101010101010101010101010101001010101010101010101010101010101 depending on the size of Int
{
    // print the txt 0b0010101010101...
    Int number = ARG(0).i;
    Int size = sizeof(Int);
    printf("0b");
    for (Int i = size * 8 - 1; i >= 0; i--) {
        printf("%d", (number >> i) & 1);
    }
    printf("\n");
    return -1;
}

LIST_FUNCTION(print_bitarray) // 00001111 00001111 00001111 11110000 or 00001111 00001111 00001111 11110000 00001111 00001111 00001111 11110000 depending on the size of Int
{
    Int number = ARG(0).i;
    Int size = sizeof(Int);
    for (Int i = size * 8 - 1; i >= 0; i--) {
        printf("%d", (number >> i) & 1);
        if (i % 8 == 0) {
            printf(" ");
        }
    }
    printf("\n");
    return -1;
}

LIST_FUNCTION(print_bytearray) // [1, 2, 3, 4] or [1, 2, 3, 4, 5, 6, 7, 8] depending on the size of Int
{
    Int number = ARG(0).i;
    Int size = sizeof(Int);
    for (Int i = 0; i < size; i++) {
        printf("%d ", (number >> (i * 8)) & 0xFF);
    }
    printf("\n");
    return -1;
}

LIST_FUNCTION(print_octal) // 0o1234567 or 0o123456789 depending on the size of Int
{
    Int number = ARG(0).i;
    printf("0o%lo\n", number);
    return -1;
}

LIST_FUNCTION(print_hex)
{
    Int i = ARG(0).i;
    printf("0x%X\n", i);
    return -1;
}

LIST_FUNCTION(print_index)
{
    Int i = ARG_I(0);
    printf("%d\n", i);
    return -1;
}

LIST_FUNCTION(print_list)
{
    List *list = (List *)ARG(0).p;
    for (Int i = 0; i < list->size; i++)
    {
        printf("%d ", list->data[i].i);
    }
    printf("\n");
    return -1;
}

INIT(io)
{
    ADD_FUNCTION(context, "print.int", print_int);
    ADD_FUNCTION(context, "print.uint", print_uint);
    ADD_FUNCTION(context, "print.float", print_float);
    ADD_FUNCTION(context, "print.string", print_string);
    ADD_FUNCTION(context, "print.bool", print_bool);
    ADD_FUNCTION(context, "print.pointer", print_pointer);
    ADD_FUNCTION(context, "print.bits", print_bits);
    ADD_FUNCTION(context, "print.bytes", print_bytearray);
    ADD_FUNCTION(context, "print.octal", print_octal);
    ADD_FUNCTION(context, "print.hex", print_hex);
    ADD_FUNCTION(context, "print.bitarray", print_bitarray);
    ADD_FUNCTION(context, "print.index", print_index);
    ADD_FUNCTION(context, "print.list", print_list);
}