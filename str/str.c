#include "buxu.h"

function(_str_concat)
{
    // pega ponteiros para as strings
    char *str1 = arg_s(0);
    char *str2 = arg_s(1);

    // salva tamanhos
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // salva a label da str2
    Value label_str2 = (Value){.s = data_l(1)};

    // cria novo bloco concatenado
    int total_len = len1 + len2 + 1;
    Int blocks = (total_len + sizeof(void*) - 1) / sizeof(void*);
    Int new_index = new_block(vm, NULL, blocks);

    // escreve str1 + str2 no novo bloco
    memcpy(&vm->values->data[new_index].u8[0], str1, len1);
    memcpy(&vm->values->data[new_index].u8[len1], str2, len2);
    vm->values->data[new_index].u8[len1 + len2] = '\0';

    // aplica a label da str1 ao novo bloco
    data_l(new_index) = arg_l(0);

    // remove os blocos antigos da str1
    for (Int i = 0; i < (len1 + 1 + sizeof(void*) - 1) / sizeof(void*); i++)
    {
        list_remove(vm->values, arg_i(0) + i);
        list_remove(vm->labels, arg_i(0) + i);
    }

    // atualiza a referência da str1
    arg_i(0) = new_index;
    arg_l(0) = NULL;

    // restaura a label da str2
    data_l(1) = label_str2.s;

    return -1;


}

init(str)
{
    add_function(vm, "str.concat", _str_concat);
}
