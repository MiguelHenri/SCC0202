#include "avl.h"

struct no {
    ITEM *info;
    NO *dir;
    NO *esq;
    int fator_b;
};

NO *no_criar(elem x) {
    NO *aux = (NO *)malloc(sizeof(NO));
    assert(aux != NULL);

    aux->info = item_criar(x);
    aux->dir = NULL;
    aux->esq = NULL;
    aux->fator_b = 0;

    return aux;
}

NO *rotacao_EE(NO *desba) {
    NO *aux = desba->dir;
    desba->dir = aux->esq;
    aux->esq = desba;

    return aux;
}

NO *rotacao_DD(NO *desba) {
    NO *aux = desba->esq;
    desba->esq = aux->dir;
    aux->dir = desba;

    return aux;
}

NO *rotacao_DE(NO *desba) {
    desba->dir = rotacao_DD(desba->dir);
    desba = rotacao_EE(desba);

    return desba;
}

NO *rotacao_ED(NO *desba) {
    desba->esq = rotacao_EE(desba->esq);
    desba = rotacao_DD(desba);

    return desba;
}

NO *no_inserir(NO *raiz, elem x, int *flag_rot, bool *flag_ins) {
    if (raiz == NULL) {//local onde posso inserir
        raiz = no_criar(x);
        *flag_rot = 1;
        *flag_ins = true;
        
        return raiz;
    }
    
    //navegando na arvore para inserir o item
    if(item_get_chave(raiz->info) < x) {
        raiz->dir = no_inserir(raiz->dir, x, flag_rot, flag_ins);
        
        if (*flag_rot == 0) {//nao tenho que verificar balanceamento
            return raiz;
        }

        if (raiz->fator_b == 1) {//equlibrei a subarvore, estava pendendo para esquerda
            raiz->fator_b = 0;
            *flag_rot = 0;
        }
        else if (raiz->fator_b == 0) {//acrescentando um no na direita
            raiz->fator_b = -1;
            *flag_rot = 1;//verificar se precisa fazer rotacao
        }
        else {//raiz->fator_b == -1, desbalanceei para direita

            if (raiz->dir->fator_b == -1) {//filho com mesmo sinal, rot simples
                raiz = rotacao_EE(raiz);
                raiz->esq->fator_b = 0;
                raiz->fator_b = 0;
                *flag_rot = 0;

                return raiz;//early return para evitar if aninhados
            }

            //pai e filho com sinais opostos, rotacao dupla neles
            raiz = rotacao_DE(raiz);

            //verificando cada caso de balanceamento
            if (raiz->fator_b == 1) {
                raiz->esq->fator_b = 0;
                raiz->dir->fator_b = -1;
            }
            else if (raiz->fator_b == 0) {
                raiz->dir->fator_b = 0;
                raiz->esq->fator_b = 0;
            }
            else {//raiz->fator_b == -1
                raiz->esq->fator_b = 1;
                raiz->dir->fator_b = 0;
            }

            raiz->fator_b = 0;
            *flag_rot = 0; //fiz o balanceamento necessario
        }
    } 
    else if(item_get_chave(raiz->info) > x) {
        raiz->esq = no_inserir(raiz->esq, x, flag_rot, flag_ins);

        if (*flag_rot == 0) {//nao tenho que verificar balanceamento
            return raiz;
        }
            
        if (raiz->fator_b == -1) {//balanceei a arvore, estava pendendo para direita
            raiz->fator_b = 0;
            *flag_rot = 0;
        }
        else if (raiz->fator_b == 0) {//acrescentando um no na esq, aumenta altura da arvore
            raiz->fator_b = 1;
            *flag_rot = 1;//verificar se precisa fazer rotacao
        }
        else {//raiz->fator_fb == 1, desbalanceei para esq

            //pai e filho tem mesmo sinal, rotacao simples
            if (raiz->esq->fator_b == 1) {
                raiz = rotacao_DD(raiz);
                raiz->dir->fator_b = 0;
                raiz->fator_b = 0;
                *flag_rot = 0;

                return raiz;//early return para evitar if aninhados
            }

            //pai e filho sinais diferentes, rotacao dupla
            raiz = rotacao_ED(raiz);

            //verificando cada caso de balanceamento da avl
            if (raiz->fator_b == -1) {
                raiz->esq->fator_b = 1;
                raiz->dir->fator_b = 0;
            }
            else if (raiz->fator_b == 0) {
                raiz->esq->fator_b = 0;
                raiz->dir->fator_b = 0;
            }
            else {//raiz->fator_b == 1
                raiz->dir->fator_b = -1;
                raiz->esq->fator_b = 0;
            }

            raiz->fator_b = 0;
            *flag_rot = 0; //fiz o balanceamento necassario
        }
    }
    //caso o elemento que queremos inserir ja esteja na arvore,
    //nehuma concicional eh satisfeita, simplesmente a raiz eh retornada

    return raiz;
}

//printa avl no formato de arvore
void no_print_as_avl(NO *raiz) {
    if(raiz != NULL) {
		printf("%d(", item_get_chave(raiz->info));
		no_print_as_avl(raiz->esq);
		printf(",");
		no_print_as_avl(raiz->dir);
		printf(")");
	} else {
		printf("_");
	}
}

//percorre arvore avl em ordem imprimindo valores
void no_print(NO *raiz) {
    if(raiz == NULL) return;
    
    no_print(raiz->esq);
    printf("%d, ", item_get_chave(raiz->info));
    no_print(raiz->dir);
}

//funcao que libera a memoria alocada
void no_demolir(NO **raiz) {
    if (*raiz == NULL) return;

    NO *aux = *raiz;
    ITEM *i = (*raiz)->info;

    no_demolir(&(*raiz)->esq);
    no_demolir(&(*raiz)->dir);
    
    item_demolir(&i);
    free(aux);
    aux = NULL;
}

void avl_copiar(NO *original, NO **copia, int *rot, bool *ins) {
    if(original == NULL) return;

    *copia = no_inserir(*copia, item_get_chave(original->info), rot, ins);
    *rot = 0;
    *ins = false;

    //chamadas recursivas para copiar a arvore inteira
    avl_copiar(original->esq, copia, rot, ins);
    avl_copiar(original->dir, copia, rot, ins);

}

//funcao que verifica se um elem pertence a uma arvore
bool no_pertence(NO *raiz, elem x) {
    if (raiz == NULL) return false;
    
    if (item_get_chave(raiz->info) == x) return true;

    if (item_get_chave(raiz->info) < x) {
        return no_pertence(raiz->dir, x);
    }
    else {
        return no_pertence(raiz->esq, x);
    }
}

NO *balanceamento_esq(NO *desba, int *flag_altura) {
    if (desba->fator_b == 1) { //tem um filho da esq, altura modificada
        desba->fator_b = 0;
    }
    else if (desba->fator_b == 0) { //estava balanceado, tira da esquerda, => -1, nao muda altura (ainda tem filho da direita)
        desba->fator_b = -1;
        *flag_altura = 0;
    }
    else { //desba->fator_b == -1

        //desabalanceou, mais filhos na direita, necessita rotacao => mudanca de altura
        //duas rotacoes possiveis
        if (desba->dir->fator_b <= 0) { //caso rotacao simples EE
            desba = rotacao_EE(desba);

            //alterando os fatores apos rotacao
            if (desba->fator_b == 0) { //filho da direita tem filho da esq
                desba->esq->fator_b = -1;
                desba->fator_b = 1;
                *flag_altura = 0; //altura nao foi modificada na rotacao 
            }
            else { // filho da direita so tem filho da direita
                desba->esq->fator_b = 0;
                desba->fator_b = 0;
                //altura eh alterada
            }
        }
        else { // rotacao dupla DE
            desba = rotacao_DE(desba);
            
            //alterando os fatores apos rotacao
            if (desba->fator_b == 1) {
                desba->esq->fator_b = 0;
                desba->dir->fator_b = -1;
            }
            else if (desba->fator_b == -1) {
                desba->esq->fator_b = 1;
                desba->dir->fator_b = 0;
            }
            else {
                desba->esq->fator_b = 0;
                desba->dir->fator_b = -1;
            }
            desba->fator_b = 0;
        }
    }

    return desba;
}

NO *balanceamento_dir(NO *desba, int *flag_altura) {
    if (desba->fator_b == -1) { //tira filho direita, -1 vai pra 0
        desba->fator_b = 0;
    }
    else if (desba->fator_b == 0) { //tira filho direita, 0 vai pra 1, nao muda altura (ha filho esquerda ainda)
        desba->fator_b = 1;
        *flag_altura = 0;
    }
    else { //necessita balanceamento, 1 vai pra 2 com remocao do filho da direita
        if (desba->esq->fator_b <= 0) { //caso rotacao simples DD
            desba = rotacao_DD(desba);

            //alterando os fatores apos rotacao
            if (desba->fator_b == 0) { 
                desba->dir->fator_b = 1;
                desba->fator_b = -1;
                *flag_altura = 0; //altura nao foi modificada na rotacao 
            }
            else {
                desba->dir->fator_b = 0;
                desba->fator_b = 0;
                //altura eh alterada
            }
        }
        else { // rotacao dupla ED
            desba = rotacao_ED(desba);
            
            //alterando os fatores apos rotacao
            if (desba->fator_b == 1) {
                desba->esq->fator_b = 0;
                desba->dir->fator_b = -1;
            }
            else if (desba->fator_b == -1) {
                desba->esq->fator_b = 1;
                desba->dir->fator_b = 0;
            }
            else {
                desba->esq->fator_b = 0;
                desba->dir->fator_b = 0;
            }
            desba->fator_b = 0;
        }
    }

    return desba;
}

//funcao que busca o maior partindo da esquerda de raiz
NO *no_get_maior_da_esq(NO *atual, NO *raiz, int *flag_altura) {
    NO *aux;

    if(atual->dir != NULL) { //ainda ha maiores, continua busca
        atual->dir = no_get_maior_da_esq(atual->dir, raiz, flag_altura);
        if (*flag_altura == 1) {
            atual = balanceamento_dir(atual, flag_altura);
        }
    }
    else { //encontrou maior
        raiz->info = atual->info;
        aux = atual;
        atual = atual->esq;
        free(aux);
        *flag_altura = 1; //remocao de folha => diminui altura.
    }

    return atual;
}

NO *no_remover(NO *raiz, elem x, int *flag_altura, int *flag_remocao) {
    if (raiz == NULL) {
        printf("Elemento nao existe para ser removido !\n");
        *flag_altura = 0;
        *flag_remocao = 0;
    }
    else if (item_get_chave(raiz->info) > x) {//elemento menor que raiz
        raiz->esq = no_remover(raiz->esq, x, flag_altura, flag_remocao);
        
        if (*flag_altura == 1) { //desbalanceou altura em relacao ao pai (raiz)
            raiz = balanceamento_esq(raiz, flag_altura);
        }
    }
    else if (item_get_chave(raiz->info) < x) {//elemento maior que raiz
        raiz->dir = no_remover(raiz->dir, x, flag_altura, flag_remocao);

        if (*flag_altura == 1) { //desbalanceou altura em relacao ao pai (raiz)
            raiz = balanceamento_dir(raiz, flag_altura);
        }
    }
    else { //elemento igual a raiz
        NO *aux = NULL;
        
        if (raiz->esq == NULL && raiz->dir == NULL) { //removendo folha
            aux = raiz;
            free(aux);
            raiz = NULL;
            *flag_altura = 1; //remove folha, diminui altura
        } 
        else if (raiz->dir == NULL) { //existe esq
            aux = raiz;
            raiz = raiz->esq;
            free(aux);
            aux = NULL;
            *flag_altura = 1; //diminui altura em 1
        }
        else if (raiz->esq == NULL) { //existe dir
            aux = raiz;
            raiz = raiz->dir;
            free(aux);
            aux = NULL;
            *flag_altura = 1; //diminui altura em 1
        }
        else { //tem filho da direita e da esquerda
            //procurar maior folha da esquerda
            raiz->esq = no_get_maior_da_esq(raiz->esq, raiz, flag_altura);
            if (*flag_altura == 1) {
                raiz = balanceamento_esq(raiz, flag_altura);
            }
        }
    }

    return raiz;
}

void avl_interseccao(NO **conj_intersec, NO *conj1, NO *conj2, int *flag_ins) {
    if (conj1 == NULL || conj2 == NULL) return;

    //se o elemento do conj 2 tambem estiver no conj 1, entao inserimos no conj interseccao
    if (no_pertence(conj1, item_get_chave(conj2->info))) {
        int flag_h = 0;
        bool flag_lixo = false; //flag nao sera usada para nada nessa funcao
        *flag_ins += 1; //flag para contabilizar qtd de itens do conj intersec

        *conj_intersec = no_inserir(*conj_intersec, item_get_chave(conj2->info), &flag_h , &flag_lixo); 
    }

    avl_interseccao(conj_intersec, conj1, conj2->esq, flag_ins);
    avl_interseccao(conj_intersec, conj1, conj2->dir, flag_ins);
}

void avl_uniao(NO **conj_uniao, NO *conj1, NO *conj2, int *flag_ins) {
    if (conj1 == NULL || conj2 == NULL) return;

    //se o elemento do conj 2 nao estiver no conj 1, entao inserimos no conj uniao,
    //pois o conj uniao ja possui todos os elementos do conj 1
    if (no_pertence(conj1, item_get_chave(conj2->info)) == false) {
        int flag_h = 0;
        bool flag_lixo = false;//flag nao sera usada para nada nessa funcao
        *flag_ins += 1; //flag para contabilizar qtd de itens do conj uniao

        *conj_uniao = no_inserir(*conj_uniao, item_get_chave(conj2->info), &flag_h , &flag_lixo); 
    }

    avl_uniao(conj_uniao, conj1, conj2->esq, flag_ins);
    avl_uniao(conj_uniao, conj1, conj2->dir, flag_ins);
}