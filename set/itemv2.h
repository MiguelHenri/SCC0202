//TAD utilizado para generalizar a aplicacao do codigo

#ifndef ITEM_H2
#define ITEM_H2

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int elem;

typedef struct item ITEM;

ITEM *item_criar(elem x);

//retorna o valor da chave que esta armazenado na struct item
elem item_get_chave(ITEM *item);

//funcao que libera memoria alocada das structs item
void item_demolir(ITEM **item);

void item_print(ITEM *item);

#endif