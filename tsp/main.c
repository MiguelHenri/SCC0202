//contributor: https://github.com/zLeonardoIshida

/*SCC0202 - Algoritmos e Estruturas de Dados I Prof. Marcelo Manzato
* 
*Alunos: 
*   Miguel Bragante Henriques
*   Leonardo Ishida
*/

#include "pcv.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    int qtd_cidades;
    scanf("%d", &qtd_cidades);
    int cid_orig;
    scanf("%d", &cid_orig);

    //alocando uma lista de cidades
    CIDADE *c = cria_cidade(qtd_cidades);
    //inicializando a lista com flags
    set_cidade_inicio(c, qtd_cidades);

    read_input(c, qtd_cidades);

    //usamos cidade_orig-1, pois a cidade 1 equivale ao indice 0
    GRAFO *g = cria_grafo(qtd_cidades, cid_orig-1);
    grafo_set_cidade(c, g);

    RESPOSTA *r = cria_resposta(qtd_cidades);

    solucao(g, 0, cid_orig-1, r); 

    print_melhor_caminho(r, qtd_cidades);

    liberar_grafo(&g);//desalocando memoria
    liberar_resposta(&r);

    return 0;
    }
