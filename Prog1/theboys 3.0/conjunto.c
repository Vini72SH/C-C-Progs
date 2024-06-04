#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "conjunto.h"

/* Busca por um elemento no vetor e devolve seu índice.
 * Devolve -1 se não encontrar. */
int Busca_Binaria(struct conjunto *c, int x){
    int ini, med, fim;

    ini = 0;
    fim = c->card - 1;
    med = (ini + fim) / 2;

    if(c->v[med] == x){
        return med;
    }

    /* Reajusta a área de busca. */
    while((ini <= fim) && (c->v[med] != x)){
        if(c->v[med] <= x){
            ini = med + 1;
        }else{
            fim = med - 1;
        }
        med = (ini + fim)/2;
    }

    if(c->v[med] == x){
        return med;
    }

    return -1;

}

/*
 * Cria um conjunto vazio e o retorna, se falhar retorna NULL.
 * max eh o tamanho maximo do conjunto, isto eh, o tamanho maximo do vetor
 */
struct conjunto *cria_cjt (int max){
    struct conjunto *Novo_Conjunto;

    /* Alocação da Struct. */
    Novo_Conjunto = malloc(sizeof(struct conjunto));
    if(Novo_Conjunto == NULL){
        return NULL;
    }

    /* Alocação do Vetor. */
    Novo_Conjunto->v = malloc((max) * (sizeof(int)));
    if(Novo_Conjunto->v == NULL){
        return NULL;
    }

    /* Atribuição das Variáveis. */
    Novo_Conjunto->max = max;
    Novo_Conjunto->card = 0;

    return Novo_Conjunto;
}

/*
 * Remove todos os elementos do conjunto, libera espaco e devolve NULL.
 */
struct conjunto *destroi_cjt (struct conjunto *c){

    if((c == NULL) || (c->v == NULL)){
        return NULL;
    }

    /* Liberação de Memória. */
    free(c->v);
    free(c); 

    return NULL;
}

/*
 * Retorna 1 se o conjunto esta vazio e 0 caso contrario.
 */
int vazio_cjt (struct conjunto *c){

    if((c == NULL) || (c->card == 0)){
        return 1;
    }

    return 0;

}

/*
 * Retorna a cardinalidade do conjunto, isto eh, o numero de elementos presentes nele.
 */
int cardinalidade_cjt (struct conjunto *c){
    
    if(c == NULL){
        return 0;
    }

    return c->card;
}

int insere_cjt (struct conjunto *c, int elemento){
    int i, j, p;

    if((c == NULL) || (c->card == c->max)){
        return 0;
    }

    /* Busca o elemento no conjunto. */
    p = Busca_Binaria(c, elemento);
    if(p >= 0){
        return 1;
    }

    /* Insere ordenado caso não aja
     * o elemento. */
    i = 0;
    while ((i < c->card) && (c->v[i] < elemento)){
        i++;
    }

    for(j = c->card - 1; j >= i; j--){
            c->v[j + 1] = c->v[j];
    }

    c->v[i] = elemento;
    c->card++;

    return 1;
}

/*
 * Remove o elemento 'elemento' do conjunto caso ele exista.
 * Retorna 1 se a operacao foi bem sucedida e 0 se o elemento nao existe.
 */
int retira_cjt (struct conjunto *c, int elemento){
    int i, j;

    if(c == NULL){
        return 0;
    }

    /*Percorre o conjunto procurando o elemento.*/
    i = Busca_Binaria(c, elemento);
    if(i < 0){
        return 0;
    }

    /* Caso encontre, remove o elemento
     * e mantém ordenado. */
    for(j = i; j < c->card - 1; j++){
        c->v[j] = c->v[j + 1];
    }

    c->card--;

    return 1;
}

/*
 * Retorna 1 se o elemento pertence ao conjunto e 0 caso contrario.
 */
int pertence_cjt (struct conjunto *c, int elemento){
    int i;

    if(c == NULL){
        return 0;
    }

    /* Busca o elemento. */
    i = Busca_Binaria(c, elemento);

    if(i < 0){
        return 0;
    }

    return 1;
}

/*
 * Retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario.
 */
int contido_cjt (struct conjunto *c1, struct conjunto *c2){
    int i;

    if((c1 == NULL) || (c2 == NULL)){
        return 0;
    }

    /* Verifica se todos os elementos de c1
     * estão contidos em c2. */
    for(i = 0; i < c1->card; i++){
        if(!(pertence_cjt(c2, c1->v[i]))){
            return 0;
        }
    }

    return 1;
}

/*
 * Retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario.
 */
int sao_iguais_cjt (struct conjunto *c1, struct conjunto *c2){
    int i;

    if((c1 == NULL) || (c2 == NULL) || (c1->card != c2->card)){
        return 0;
    }

    /* Verifica todos os elementos dos conjuntos. */
    for(i = 0; i < c1->card; i++){
        if(c1->v[i] != c2->v[i]){
            return 0;
        }
    }

    return 1;
}

/*
 * Cria e retorna o conjunto diferenca entre c1 e c2, nesta ordem.
 * Retorna NULL se a operacao falhou.
 */
struct conjunto *diferenca_cjt (struct conjunto *c1, struct conjunto *c2){
    int i;
    struct conjunto *dif;

    if((c1 == NULL) || (c2 == NULL)){
        return NULL;
    }

    /* Criação do conjunto. */
    dif = cria_cjt(c1->max);
    if(dif == NULL){
        return NULL;
    }

    /* Insere os elementos de c1. */
    for(i = 0; i < c1->card; i++){
        insere_cjt(dif, c1->v[i]);
    }

    /* Remove os elementos de c2. */
    for(i = 0; i < c2->card; i++){
        retira_cjt(dif, c2->v[i]);
    }

    return dif;
}

/*
 * Cria e retorna o conjunto interseccao entre os conjuntos c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
struct conjunto *interseccao_cjt (struct conjunto *c1, struct conjunto *c2){
    int i;
    struct conjunto *inter;

    if((c1 == NULL) || (c2 == NULL)){
        return NULL;
    }

    /* Criação do Conjunto. */
    inter = cria_cjt(c1->max);
    if(inter == NULL){
        return NULL;
    }

    /* Insere apenas os elementos
     * em comum. */
    for(i = 0; i < c1->card; i++){
        if(pertence_cjt(c2, c1->v[i])){
            insere_cjt(inter, c1->v[i]);
        }
    }

    return inter;
}

/*
 * Cria e retorna o conjunto uniao entre os conjunto c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
struct conjunto *uniao_cjt (struct conjunto *c1, struct conjunto *c2){
    int i;
    struct conjunto *uni;

    if((c1 == NULL) || (c2 == NULL)){
        return NULL;
    }

    /* Criação do Conjunto. */
    uni = cria_cjt(c1->max + c2->max);
    if(uni == NULL){
        return NULL;
    }

    /* Inserção dos elementos  de c1. */
    for(i = 0; i < c1->card; i++){
        insere_cjt(uni, c1->v[i]);
    }

    /* Inserção dos elementos de c2. */
    for(i = 0; i < c2->card; i++){
        insere_cjt(uni, c2->v[i]);
    }

    return uni;
}

/*
 * Cria e retorna uma copia do conjunto c e NULL em caso de falha.
 */
struct conjunto *copia_cjt (struct conjunto *c){
    int i;
    struct conjunto *copy;

    if(c == NULL){
        return NULL;
    }

    /* Criação do conjunto. */
    copy = cria_cjt(c->max);
    if(copy == NULL){
        return NULL;
    }

    /* Insere os elementos de c. */
    for(i = 0; i < c->card; i++){
        insere_cjt(copy, c->v[i]);
    }

    return copy;
}

struct conjunto *cria_subcjt_cjt (struct conjunto *c, int n){
    int i;
    struct conjunto *sub;

    /* Devolve uma cópia do conjunto. */
    if(n >= c->card){
        sub = copia_cjt(c);

        return sub;
    }

    /* Criação do conjunto. */
    sub = cria_cjt(n);
    if(sub == NULL){
        return sub;
    }

    /* Inserção de elementos aleatórios. */
    while(sub->card < sub->max){
        i = rand() % c->card;
        insere_cjt(sub, c->v[i]);
    }

    return sub;
}

void imprime_cjt (struct conjunto *c){
    int i;

    /* Impressão dos elementos. */
    printf("[ ");
    if(c != NULL){
        for(i = 0; i < c->card; i++){
            printf("%d ", c->v[i]);            
        }
    }
    printf("]\n");
}


/*
 * Inicializa ptr usado na funcao incrementa_iterador 
 */
void inicia_iterador_cjt (struct conjunto *c){
    if(c == NULL){
        return;
    }

    c->ptr = 0;
}

/*
 * Devolve no parametro ret_iterador o elemento apontado e incrementa o iterador.
 * A funcao retorna 0 caso: (1) o iterador ultrapasse o ultimo elemento ou
 * (2) o conjunto eh vazio. A funcao retorna 1 caso o iterador aponte para um 
 * elemento valido (dentro do conjunto).
 */
int incrementa_iterador_cjt (struct conjunto *c, int *ret_iterador){

    if((c != NULL) && (c->ptr < c->card)){
        (*ret_iterador) = c->v[c->ptr];
        c->ptr++;

        return 1;
    }

    return 0;
}

/*
 * Escolhe um elemento qualquer do conjunto para ser removido, o remove e
 * o retorna.
 * Nao faz teste se conjunto eh vazio, deixa para main fazer isso       
 */
int retira_um_elemento_cjt (struct conjunto *c){
    int i, d;

    if(c == NULL){
        return -1;
    }

    i = rand() % c->card;
    d = c->v[i];
    retira_cjt(c, c->v[i]);

    return d;
}