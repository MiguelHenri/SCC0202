//contributor: https://github.com/zLeonardoIshida

/*SCC0202 - Algoritmos e Estruturas de Dados I Prof. Marcelo Manzato
* 
*Alunos: 
*   Miguel Bragante Henriques, NUSP: 13671894
*   Leonardo Ishida, NUSP: 12873424
*/

#ifndef PCV_H
#define PCV_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    //grafo com vetor melhor sol, menor dist

    typedef struct grafo GRAFO;
    typedef struct caminho CAMINHO;
    typedef struct cidade CIDADE;
    typedef struct resposta RESPOSTA;

    // prametros:
    //     int qtd_cid: tamanho da lista de cidades a ser alocada dinamicamente
    // retorno:
    //     ponteiro para a lista de cidades criada
    CIDADE *cria_cidade(int qtd_cid);

    // parametros:
    //     CIDADE *cidades: endereco com a lista de cidades
    //     int qtd_cid: quantidade de cidades alocadas
    void set_cidade_inicio(CIDADE *cidades, int qtd_cid);

    // parametros:
    //     int qtd_cid: tamanho da fila de cidades que sera alocado
    // retorno:
    //     endereco para a lista de cidades, que possuem variaveis inicializadas com valores flag
    CAMINHO *cria_caminho(int qtd_cid);

    // parametros:
    //     CIDADE *cidades: endereco com a lista de cidades que tera seu valor alterado
    //     int orig: numero da cidade que eh a origem do caminho
    //     int dest: numero da ciade que eh o destino do caminho
    //     int peso: o custo do caminho da cidade orig ate cidade dest
    void set_caminho(CIDADE *cidades, int orig, int dest, int peso);

    // parametros:
    //     int n_vert: quantidade total de cidades
    //         (sera util para fazer condicao de parada dos iteradores)
    //     int cidade_inicial: cidade no qual o viajante comeca
    // retorno:
    //     endereco de memoria do tipo GRAFO
    GRAFO *cria_grafo(int n_vert, int cidade_inicial);

    // parametros:
    //     CIDADE *cidade: endereco da lista de cidades que sera alocada no grafo
    //     GRAFO *g: endereco do grafo que ira receber a lista de cidades
    void grafo_set_cidade(CIDADE *cidades, GRAFO *g);

    //funcao para debug
    void print(CIDADE *c, int qtd_cid);

    // parametros:
    //     CIDADE *c: endereco da lista de cidades que vai ter seus dados modificados conforme o input
    //     int qtd_cidades: quantidade maxima de cidades para ter condicao de parado dos lacos
    void read_input(CIDADE *c, int qtd_cidades);

    // parametros:
    //     GRAFO *g: endereco do grafo
    //     int num_cidades: variavel que serve como condicao de parada do backtracking
    //     int cidade_atual: valor da cidade no qual o viajante esta inicialmente
    //     RESPOSTA *r: struct que contem os enderecos dos vetores que armazenam os ids das cidades
    //          tanto do melhor caminho quanto do caminho atual. Essa struct tambem armazena os valores
    //          do melhor caminho e caminho atual
    void solucao(GRAFO *g, int num_cidades, int cidade_atual, RESPOSTA *r);
    
    // parametros:
    //     GRAFO *g: endereco do grafo
    //     RESPOSTA *r: struct com informacao das distancia e caminhos
    void atualiza_melhor_caminho(GRAFO *g, RESPOSTA *r);

    //parametros:
    //      int qtd_cid: numero de cidades para alocar os vetores dos caminhos
    //retorno:
    //      endereco para a struct ja inicializada
    RESPOSTA *cria_resposta(int qtd_cid);

    // parametros:
    //     GRAFO *g: grafo utilizado no backtracking
    //     int cidade_atual: cidade que esta procurando a origem
    //     RESPOSTA *r: struct com a resposta do backtracking, que pode ser atulizado
    //     int *i: passado como referencia para saber qual eh indice da lista de adjacencia
    //         na funcao solucao
    // retorno:
    //     se encontrou verdadeiro, caso contrario retorna falso
    bool achou_cidade_orig(GRAFO *g, int cidade_atual, RESPOSTA *r, int *i);

    void print_melhor_caminho(RESPOSTA *r, int qtd_cid);

    void liberar_grafo(GRAFO **g);

    void liberar_resposta(RESPOSTA **r);

#endif
