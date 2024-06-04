#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "conjunto.h"

struct conjunto *cria_cjt (int max){
    struct conjunto *novoConjunto;

    /*Alocação do Conjunto.*/
    novoConjunto = malloc(sizeof(struct conjunto));
    if(novoConjunto == NULL){
        return NULL;
    }

    novoConjunto->max = max;
    novoConjunto->card = 0;

    /*Alocação do Vetor.*/
    novoConjunto->v = malloc(max * sizeof(int));
    if(novoConjunto->v == NULL){
        free(novoConjunto);

        return NULL;
    }
    /*Em qualquer falha, retorna NULL.*/

    return novoConjunto;
}

struct conjunto *destroi_cjt (struct conjunto *c){

    if((c == NULL) || (c->v == NULL)){
        return NULL;
    }
    
    /*Liberação de Memória.*/
    free(c->v);
    free(c);

    return NULL;
}

int vazio_cjt (struct conjunto *c){

    /*Conjunto não vazio ou não alocado.*/
    if((c == NULL) || (c->card != 0)){
        return 0;
    }

    /*Conjunto vazio.*/
    return 1;
}

int cardinalidade_cjt (struct conjunto *c){
	return c->card;
}

int insere_cjt (struct conjunto *c, int elemento){
    int i, j;

    /*Conjunto cheio.*/
    if(c->card == c->max){
        return 0;
    }

    /*Insere na primeira posição.*/
    if(vazio_cjt(c)){
        c->v[c->card] = elemento;
        c->card++;
        return 1;
    }

    /*Percorre o conjunto procurando o lugar correto.*/
    i = 0;
    while((i < c->card) && (c->v[i] < elemento)){
        i++;
    }

    /*Se existir, retorna 1.*/
    if((i < c->card) && (c->v[i] == elemento)){
        return 1;
    }

    /*Se não, insere ordenado no conjunto.*/
    for(j = c->card-1; j >= i; j--){
        c->v[j+1] = c->v[j];
    }

    c->v[i] = elemento;
    c->card++;

    return 1;
}

int retira_cjt (struct conjunto *c, int elemento){
    int i, j;

    /*Busca o elemento no conjunto.*/
    i = 0;
    while((i < c->card) && (c->v[i] != elemento)){
        i++;
    }

    /*Não está no conjunto.*/
    if(i >= c->card){
        return 0;
    }

    /*Remoção do elemento.*/
    for(j = i; j < c->card-1; j++){
        c->v[j] = c->v[j+1];
    }

    c->card--;

    return 1;
}

int pertence_cjt (struct conjunto *c, int elemento){
    int i;

    /*Procura o elemento.*/
    i = 0;
    while((i < c->card) && (c->v[i] != elemento)){
        i++;
    }

    /*Retorna 1 se encontrou.*/
    if((i < c->card) && (c->v[i] == elemento)){
        return 1;
    }

    return 0;
}

int contido_cjt (struct conjunto *c1, struct conjunto *c2){
    int i;

    if(c1->card > c2->card){
        return 0;
    }

    /*Verifica se c1 está contido em c2.
        Retorna 1 se estiver contido.
    */
    for(i = 0; i < c1->card; i++){
        if(!(pertence_cjt(c2, c1->v[i]))){
            return 0;
        }
    }

    return 1;
}

int sao_iguais_cjt (struct conjunto *c1, struct conjunto *c2){
    int i;

    if(c1->card != c2->card){
        return 0;
    }

    i = 0;
    while((i < c1->card)){
        if(c1->v[i] != c2->v[i]){
            return 0;
        }
        i++;
    }

    return 1;
}

struct conjunto *diferenca_cjt (struct conjunto *c1, struct conjunto *c2){
    int i;
    struct conjunto *dif;

    /*Cria e aloca memória.*/
    dif = copia_cjt(c1);
    if(dif == NULL){
        return NULL;
    }

    /*Retira de c1 os elementos de c2.*/
    for(i = 0; i < c2->card; i++){
        retira_cjt(dif, c2->v[i]);
    }

    return dif;
}

struct conjunto *interseccao_cjt (struct conjunto *c1, struct conjunto *c2){
    struct conjunto *intersec;

    /*Alocação de Memória.*/
    intersec = cria_cjt(c1->max);
    if (intersec == NULL) {
        return NULL; 
    }

    /*Insere apenas elementos presentes em 
      ambos os conjuntos c1 e c2.*/
    for (int i = 0; i < c1->card; i++) {
        if (pertence_cjt(c2, c1->v[i])) {
            insere_cjt(intersec, c1->v[i]);
        }
    }

    return intersec;
}

struct conjunto *uniao_cjt (struct conjunto *c1, struct conjunto *c2){
    int i;
    struct conjunto *uniao;

    /*Alocação de Memória.*/
    uniao = cria_cjt(c1->max + c2->max);
    if(uniao == NULL){
        return NULL;
    }

    if(uniao->v == NULL){
        return NULL;
    }

    /*Insere os elementos de c1.*/
    for(i = 0; i < c1->card; i++){
        insere_cjt(uniao, c1->v[i]);
    }

    /*Insere os elementos de c2.*/
    for(i = 0; i < c2->card; i++){
        insere_cjt(uniao, c2->v[i]);
    }

    return uniao;
}

struct conjunto *copia_cjt (struct conjunto *c){
    int i;
    struct conjunto *copia;

    /*Alocação de Memória.*/
    copia = cria_cjt(c->max);
    if(copia == NULL){
        return NULL;
    }

    /*Copia os elementos para outro conjunto.*/
    for(i = 0; i < c->card; i++){
        insere_cjt(copia, c->v[i]);
    }

    return copia;
}

struct conjunto *cria_subcjt_cjt (struct conjunto *c, int n){
	int i;
    struct conjunto *subcon;

    /*Retorna uma cópia do conjunto original
      caso n >= cardinalidade (c).*/
    if(n >= c->card){
        subcon = copia_cjt(c);
        
        return subcon;
    }

    /*Alocação de Memória.*/
    subcon = cria_cjt(n);
    if(subcon == NULL){
        return NULL;
    }

    /*Conjunto vazio.*/
    if(n == 0){
        return subcon;
    }

    /*Preenchimento com valores aleatórios.*/
    while(subcon->card < n){
        i = rand() % c->card;
        insere_cjt(subcon, c->v[i]);
    }

    return subcon;
}

void imprime_cjt (struct conjunto *c){
    int i;

    /*Conjunto vazio.*/
    if(vazio_cjt(c)){
        printf("[ ]\n");
        return;
    }

    /*Impressão dos elementos.*/
    printf("[ ");
    for(i = 0; i < c->card; i++){
        printf("%d ", c->v[i]);
    }
    printf("]\n");
}

void inicia_iterador_cjt (struct conjunto *c){
    /*Inicialização.*/
    c->ptr = 0;
}

int incrementa_iterador_cjt (struct conjunto *c, int *ret_iterador){

    /*Incremento do Iterador e devolução do elemento.*/
    if((c != NULL) && (c->ptr < c->card)){
        *ret_iterador = c->v[c->ptr];
        c->ptr++;

        return 1;
    }

    return 0;
}

int retira_um_elemento_cjt (struct conjunto *c){
    int i, elemento;

    /*Retira um elemento aleatório do conjunto.*/
    i = rand() % c->card;
    elemento = c->v[i];

    retira_cjt(c, elemento);

    return elemento;
}
