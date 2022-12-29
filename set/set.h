#ifndef SET_H
#define SET_H

#include "avl.h"
#include <stdbool.h>

typedef struct set SET;

SET *set_criar();

void set_inserir(SET *s, elem x);

void set_print_as_avl(SET *s);

void set_print(SET *s);

void set_menu();

//funcao que, dado um conjunto, retorna um enderco para um outro conjunto com os 
//mesmos elementos do conjunto passado como parametro
SET *set_copia(SET *s);

bool set_pertence(SET *s, elem x);

//funcao que, dado dois conjuntos, retorna o endereco para um conjunto,
//cujos os elementos seguem a propriedade de interseccao entre conjuntos 
SET *set_interseccao(SET *s1, SET *s2);

//funcao que, dado dois conjuntos, retorna o endereco para um conjunto,
//cujos os elementos seguem a propriedade de uniao entre conjuntos 
SET *set_uniao(SET *s1, SET *s2);

bool set_remover(SET *s, elem x);

void set_demolir(SET **s);

#endif