#ifndef AVL_H
#define AVL_H

#include "itemv2.h"

typedef struct no NO;

NO *no_criar(elem x);

//funcao que insere um elem em uma arvore avl
NO *no_inserir(NO *raiz, elem x, int *flag_rot, bool *flag_ins);

//funcao que, dado uma raiz de uma arvore, e um ponteiro para raiz de outra,
//copia uma arvore para outra
void avl_copiar(NO *original, NO **copia, int *rot, bool *ins);

//funcao que printa a avl em formato de arvore em pre ordem
void no_print_as_avl(NO *raiz);

//funcao que printa a avl seguindo o modo em ordem
void no_print(NO *raiz);

void no_demolir(NO **raiz);

bool no_pertence(NO *raiz, elem x);

//funcao que remove um elemento de uma arvore
NO *no_remover(NO *raiz, elem x, int *flag_altura, int *flag_remocao);

//funcao que dado a raiz de dois conjuntos e um ponteiro para raiz do conjunto interseccao
//insere os elementos da intersseccao entre os dois conjuntos
void avl_interseccao(NO **conj_intersec, NO *conj1, NO *conj2, int *flag_ins);

//funcao que dado a raiz de dois conjuntos e um ponteiro para raiz do conjunto uniao
//que, inicialmente, eh uma copia do conjunto 1, insere os elementos do conjunto 2 que
//ainda nao fazem parte do uniao
void avl_uniao(NO **conj_uniao, NO *conj1, NO *conj2, int *flag_ins);

#endif