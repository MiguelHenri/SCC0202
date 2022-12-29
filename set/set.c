#include "set.h"
#include "avl.h"

struct set {
    NO *inicio;
    int n_itens;
};

SET *set_criar() {
    SET *aux = (SET *)malloc(sizeof(SET));
    assert(aux != NULL);

    aux->inicio = NULL;
    aux->n_itens = 0;

    return aux;
}

// funcao que libera a memoria alocada 
void set_demolir(SET **c) {
    no_demolir(&((*c)->inicio));

    free(*c);
    *c = NULL;
}

//funcao que printa uma menu de operacoes
void set_menu() {
    printf("\n======================\n");
    printf("1| Pertence\n");
    printf("2| Uniao\n");
    printf("3| Interseccao\n");
    printf("4| Printar conjuntos\n");
    printf("0| Sair\n");
    printf("======================\n");
    printf("Digite uma opcao: ");
}

//funcao que insere um elemento em um conjunto
void set_inserir(SET *s, elem x) {
    int flag_r = 0;
    bool flag_i = false;

    s->inicio = no_inserir(s->inicio, x, &flag_r, &flag_i);

    if (flag_i)
        s->n_itens += 1;
}

SET *set_copia(SET* s){
    SET *new = set_criar();
    int flag_r = 0;
    bool flag_i = false;

    new->n_itens = s->n_itens;

    avl_copiar(s->inicio, &new->inicio, &flag_r, &flag_i);

    return new;
}

//funcao que printa o conjunto como uma arvore, de modo pre ordem
void set_print_as_avl(SET *s) {
    no_print_as_avl(s->inicio);
    printf("\nQuantidade de elementos: %d\n", s->n_itens);
}

//funcao que printa o conjunto de modo em ordem
void set_print(SET *s) {
    no_print(s->inicio);
    printf("Quantidade de elementos: %d\n", s->n_itens);
}

//funcao que verifica se um elemento pertence a um conjunto
bool set_pertence(SET *s, elem x) {
    return no_pertence(s->inicio, x);
}

//funcao que remove um elemento do conjunto
bool set_remover(SET *s, elem x) {
    int flag_altura = 0;
    int flag_remocao = 1;

    s->inicio = no_remover(s->inicio, x, &flag_altura, &flag_remocao);
    if(flag_remocao == 1) {
        s->n_itens -= 1;
        return true; //removeu
    }
    else 
        return false; //nao removeu
}

SET *set_interseccao(SET *s1, SET *s2) {
    SET *intersec = set_criar();

    int flag_insercao = 0;
    avl_interseccao(&(intersec->inicio), s1->inicio, s2->inicio, &flag_insercao);

    intersec->n_itens += flag_insercao; 

    return intersec;
}

SET *set_uniao(SET *s1, SET *s2) {
    SET *uniao = set_criar();
    uniao = set_copia(s1);

    int flag_uniao = 0;
    avl_uniao(&uniao->inicio, s1->inicio, s2->inicio, &flag_uniao);
    
    uniao->n_itens += flag_uniao;

    return uniao;
}
