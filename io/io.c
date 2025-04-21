#include "buxu.h"

function(print_int)
{
    printf("%d\n", arg(0).i);
    return -1;
}

function(print_float)
{
    printf("%f\n", arg(0).f);
    return -1;
}

function(print_string)
{
    printf("%s\n", arg_s(0));
    return -1;
}

function(print_bool)
{
    printf("%s\n", arg(0).i ? "true" : "false");
    return -1;
}

function(print_pointer)
{
    printf("%p\n", arg(0).p);
    return -1;
}

function(print_bits) // 0b01010101010101010101010101010101 or 0b1010101010101010101010101010101001010101010101010101010101010101 depending on the size of Int
{
    Int number = arg(0).i;
    Int size = sizeof(Int);
    for (Int i = size * 8 - 1; i >= 0; i--) {
        printf("%d", (number >> i) & 1);
    }
    printf("\n");
    return -1;
}

function(print_bitarray) // 00001111 00001111 00001111 11110000 or 00001111 00001111 00001111 11110000 00001111 00001111 00001111 11110000 depending on the size of Int
{
    Int number = arg(0).i;
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

function(print_bytearray) // [1, 2, 3, 4] or [1, 2, 3, 4, 5, 6, 7, 8] depending on the size of Int
{
    Int number = arg(0).i;
    Int size = sizeof(Int);
    for (Int i = 0; i < size; i++) {
        printf("%d ", (number >> (i * 8)) & 0xFF);
    }
    printf("\n");
    return -1;
}

function(print_octal) // 0o1234567 or 0o123456789 depending on the size of Int
{
    Int number = arg(0).i;
    printf("0o%lo\n", number);
    return -1;
}

function(print_hex)
{
    Int i = arg(0).i;
    printf("0x%X\n", i);
    return -1;
}

init(io)
{
    add_function(vm, "print.int", print_int);
    add_function(vm, "print.float", print_float);
    add_function(vm, "print.string", print_string);
    add_function(vm, "print.bool", print_bool);
    add_function(vm, "print.pointer", print_pointer);
    add_function(vm, "print.bits", print_bits);
    add_function(vm, "print.bytes", print_bytearray);
    add_function(vm, "print.octal", print_octal);
    add_function(vm, "print.hex", print_hex);
    add_function(vm, "print.bitarray", print_bitarray);
}