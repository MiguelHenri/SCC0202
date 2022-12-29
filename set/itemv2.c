#include "itemv2.h"

struct item {
    elem key;
};

ITEM *item_criar(elem x) {
    ITEM *aux = (ITEM *)malloc(sizeof(ITEM));
    assert(aux != NULL);

    aux->key = x;

    return aux;
}

elem item_get_chave(ITEM *item) {
    assert(item != NULL);
    return item->key;
}

void item_demolir(ITEM **item) {
    if (item == NULL || *item == NULL) return;
    
    free(*item);
    *item = NULL;
}

void item_print(ITEM *item) {
    printf("%d,", item->key);
}