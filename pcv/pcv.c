//contributor: https://github.com/zLeonardoIshida

/*SCC0202 - Algoritmos e Estruturas de Dados I Prof. Marcelo Manzato
* 
*Alunos: 
*   Miguel Bragante Henriques, NUSP: 13671894
*   Leonardo Ishida, NUSP: 12873424
*/

#include "pcv.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct cidade {
    int id;        // valor da cidade
    bool foi_usado;     // sera usado no backtracking
    CAMINHO *lista_adj; // lista de caminhos, lista de adjacencia
};

struct grafo {
    int n_vertices;
    int cidade_inicial;
    CIDADE *cidades; // lista de cidades
};

struct caminho {
    int origem;
    int destino;
    int distancia; // ou custo/peso
};

struct resposta {
    int *melhor_caminho;
    int *caminho_atual;
    int *distancia_atual;
    int *distancia_menor;
};

CIDADE *cria_cidade(int qtd_cid) {
    // essa funcao aloca memoria para um vetor de cidades, que sera usado no nosso
    // grafo
    CIDADE *c = (CIDADE *)malloc(sizeof(CIDADE) * qtd_cid);
    assert(c != NULL); // erro de alocacao

    return c;
}

void set_cidade_inicio(CIDADE *cidades, int qtd_cid) {
    // essa funcao seta as cidades no comeco do programa, serve para inicializar
    // valores, bem como criar as listas de adjacencia, alocando memoria
    assert(cidades != NULL);
    for (int i = 0; i < qtd_cid; i++) {
        cidades[i].id = i + 1;
        cidades[i].foi_usado = false;
        cidades[i].lista_adj = cria_caminho(qtd_cid); // chama funcao que aloca memoria para os caminhos
    }
}

CAMINHO *cria_caminho(int qtd_cid) {
    // essa funcao cria o vetor de caminhos, que sera usado como lista de
    // adjacencia para cada cidade
    CAMINHO *novo = (CAMINHO *)malloc(sizeof(CAMINHO) * qtd_cid); // alocando espaco
    assert(novo != NULL);                             // erro de alocacao

    // setando os valores para -1 como default, sera usado para efetivamente dar
    // valores aos caminhos no futuro
    for (int i = 0; i < qtd_cid; i++) {
        novo[i].origem = -1;
        novo[i].destino = -1;
        novo[i].distancia = -1;
    }

    return novo;
}

void set_caminho(CIDADE *cidades, int orig, int dest, int peso) {
    // essa funcao da valores a um novo caminho no vetor de caminhos de uma cidade
    // origem
    assert(cidades != NULL);

    int i = 0;
    // como cidade 1 equivale a cidade indice 0 no vetor, acessamos origem - 1
    // quando cidades[orig-1].lista_adj[i].origem==-1, o caminho na posicao i nao
    // foi criado ainda aqui, contamos quantos i caminhos nao foram criados ainda,
    // assim, o caminho criado tera posicao i lembrando que para um vetor de x
    // elementos, o elemento "proximo" eh o de indice x
    if (cidades[orig - 1].lista_adj[i].origem != -1) {
        while (cidades[orig - 1].lista_adj[i].origem != -1) {
            i++;
        }
    }

    // setando os valores do novo caminho
    cidades[orig - 1].lista_adj[i].origem = orig;
    cidades[orig - 1].lista_adj[i].destino = dest;
    cidades[orig - 1].lista_adj[i].distancia = peso;

    i = 0;
    if (cidades[dest - 1].lista_adj[i].origem != -1) {
        while (cidades[dest - 1].lista_adj[i].origem != -1) {
            i++;
        }
    }

    cidades[dest - 1].lista_adj[i].origem = dest;
    cidades[dest - 1].lista_adj[i].destino = orig;
    cidades[dest - 1].lista_adj[i].distancia = peso;
}

GRAFO *cria_grafo(int n_vert, int cidade_inicial) {
    // essa funcao aloca memoria para o nosso grafo
    GRAFO *novo = (GRAFO *)malloc(sizeof(GRAFO));
    assert(novo != NULL); // erro de alocacao

    // inicializando
    novo->n_vertices = n_vert;
    novo->cidades = NULL;
    novo->cidade_inicial = cidade_inicial;

    return novo;
}

void grafo_set_cidade(CIDADE *cidades, GRAFO *g) {
    // essa funcao atribui nossas cidades para o nosso grafo
    assert(cidades != NULL);
    assert(g != NULL);

    g->cidades = cidades;
}

void print(CIDADE *c, int qtd_cid) {
    // funcao usada apenas para debugar a leitura dos dados
    for (int i = 0; i < qtd_cid; i++) {
        printf("\nCidade %d:\n", i + 1);
        printf("Caminhos: \n");
        for (int j = 0; j < qtd_cid; j++) {
            if (c[i].lista_adj[j].destino != -1) {
                printf("Origem: %d, ", c[i].lista_adj[j].origem);
                printf("Destino: %d, ", c[i].lista_adj[j].destino);
                printf("Distancia: %d\n", c[i].lista_adj[j].distancia);
            }
        }
    }
}

void read_input(CIDADE *c, int qtd_cidades) {
    assert(c != NULL);
    // essa funcao faz a leitura dos caminhos, armazenando-os nas estruturas de dados
    int orig;
    int dest;
    int peso;

    while (scanf("%d", &orig) != EOF) {
        scanf("%d", &dest);
        scanf("%d", &peso);

        set_caminho(c, orig, dest, peso);
    }
}

bool achou_cidade_orig(GRAFO *g, int cidade_atual, RESPOSTA *r, int *i){
    bool achou_cidade = false;
    int n = g->n_vertices;

    // percorrendo a lista para verificar se ha um caminho para cidade original
    for (*i = 0; *i < n; *i += *i +1) {
        if (g->cidades[cidade_atual].lista_adj[*i].destino-1 == g->cidade_inicial) {
            *(r->distancia_atual) += g->cidades[cidade_atual].lista_adj[*i].distancia;
            achou_cidade = true;
            break;
        } 
    }

    return achou_cidade;
}


void solucao(GRAFO *g, int num_cidades, int cidade_atual, RESPOSTA *r) {
    assert(g != NULL && r != NULL);

    int qtd_cid = g->n_vertices;

    //fixando a ultima cidade do backtracking
    if (num_cidades == qtd_cid - 1) {
        r->caminho_atual[num_cidades] = g->cidades[cidade_atual].id;
        int i;

        // nao encontrou um caminho para voltar a origem. Esse caminho nao serve para solucao final
        //necessario passar i como parametro para subtrair depois da chamada recursiva, o valor correto
        if (achou_cidade_orig(g, cidade_atual, r, &i) == false) { 
            return;
        }
        
        solucao(g, num_cidades + 1, g->cidades[cidade_atual].lista_adj[0].destino - 1, r);
        *(r->distancia_atual) -= g->cidades[cidade_atual].lista_adj[i].distancia;
    }

    //ultima verificacao da etapa de backtracking, todas cidades fixadas
    if (num_cidades == qtd_cid) {
        //verificacao no if com -1 pq inicializamos com essa valor para ser uma flag
        if (*(r->distancia_atual) < *(r->distancia_menor) || *(r->distancia_menor) == -1) {
            atualiza_melhor_caminho(g, r);
        }
    
        return;
    }

    for (int i = 0; i < qtd_cid; i++) {

        if (g->cidades[g->cidades[cidade_atual].lista_adj[i].destino - 1].foi_usado == true)
            continue; // caso onde o caminho encontrado eh para uma cidade ja acessada

        if (g->cidades[cidade_atual].lista_adj[i].destino == -1) 
            continue; // caso onde nao ha caminho

        //fixando uma cidade e adicionando ela na possivel solucao
        g->cidades[cidade_atual].foi_usado = true;
        r->caminho_atual[num_cidades] = g->cidades[cidade_atual].lista_adj[i].origem;
        *(r->distancia_atual) += g->cidades[cidade_atual].lista_adj[i].distancia;

        //chamada recursiva para resolver o que falta do problema
        solucao(g, num_cidades + 1, g->cidades[cidade_atual].lista_adj[i].destino - 1, r);

        //desfixando e subtraindo o valor do caminho da distancia atual
        g->cidades[cidade_atual].foi_usado = false;
        *(r->distancia_atual) -= g->cidades[cidade_atual].lista_adj[i].distancia;
    }         
}

void atualiza_melhor_caminho(GRAFO *g, RESPOSTA *r) {
    //nao preciso fazer a verificacao se os ponteiros sao nulos pq ja fiz em solucao
    int qtd_cidades = g->n_vertices + 1;
    int i;

    for (i = 0; i < qtd_cidades; i++) {
        r->melhor_caminho[i] = r->caminho_atual[i];
    }

    //inserindo a cidade inicial no vetor que armazena o melhor caminho
    r->melhor_caminho[i-1] = g->cidade_inicial + 1;

    //atualizando o menor caminho
    *(r->distancia_menor) = *(r->distancia_atual);
}

RESPOSTA *cria_resposta(int qtd_cid) {
    RESPOSTA *r = (RESPOSTA *)malloc(sizeof(RESPOSTA));
    assert(r != NULL);

    //qtd_cid + 1 pq tem que incluir a cidade de origem
    r->melhor_caminho = (int *)malloc(sizeof(int) * (qtd_cid+1));
    assert(r->melhor_caminho != NULL);

    r->caminho_atual = (int *)malloc(sizeof(int) * qtd_cid);
    assert(r->caminho_atual != NULL);

    //setando para -1 pois eh uma flag
    r->distancia_menor = (int *)malloc(sizeof(int));
    assert(r->distancia_menor != NULL);
    *(r->distancia_menor) = -1;

    r->distancia_atual = (int *)malloc(sizeof(int));
    assert(r->distancia_atual != NULL);
    *(r->distancia_atual) = 0;

    return r;
}

void print_melhor_caminho(RESPOSTA *r, int qtd_cid) {
    assert(r != NULL);

    for (int i = 0; i < qtd_cid+1; i++) 
        printf("%d ", r->melhor_caminho[i]);

    printf("\n");
}

/*desaloca memoria utilizada pelo programa no grafo, cidades, caminhos*/
void liberar_grafo(GRAFO **g) {
    assert(g != NULL);

    int n = (*g)->n_vertices;

    for (int i = 0; i < n; i++) {
        free((*g)->cidades[i].lista_adj);
    }

    free((*g)->cidades);
    (*g)->cidades = NULL;

    free(*g);
    *g = NULL;
}

/*desaloca memoria utilizada para as respostas*/
void liberar_resposta(RESPOSTA **r) {
    assert(r != NULL);

    free((*r)->caminho_atual);
    (*r)->caminho_atual = NULL;

    free((*r)->melhor_caminho);
    (*r)->melhor_caminho = NULL;

    free((*r)->distancia_atual);
    (*r)->distancia_atual = NULL;

    free((*r)->distancia_menor);
    (*r)->distancia_menor = NULL;

    free(*r);
    *r = NULL;
}
