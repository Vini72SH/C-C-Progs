#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

/* Cria uma lista encadeada 
 * Retorna: Ponteiro para lista. */
lista *criaLista (){
    struct lista *l;

    l = malloc(sizeof(struct lista));
    if (!l) return NULL;

    l->tam = 0;
    l->prime = NULL;
    l->ult = NULL;

    return l;
}

/* Retorna 1 se a lista estiver vazia
 * e 0 caso contrário. */
int listaVazia(struct lista *l){
    if(!l) return 0;

    if(l->tam == 0) return 1;
    
    return 0;
}

/* Cria um nodo com as string s e indíce i
 * Retorna: Ponteiro para o nodo. */
nodo *criaNodo (char *s, int i){
    struct nodo *novo;

    /* Alocação de Memória. */
    novo = malloc(sizeof(struct nodo));
    if(!novo) return NULL;

    novo->ind = i;
    novo->string = strdup(s);
    novo->prox = NULL;

    return novo;
}

/* Insere a string s no fim da lista. */
int insereL(struct lista *l, char *s, int ind){
    struct nodo *no;

    if(!l) return 0;

    /* Criação do nodo. */
    no = criaNodo(s, ind);
    if(!no) return 0;

    /* Insere na lista de forma correta.
     * No começo ou no final. */
    if(listaVazia(l)){
        l->prime = no;
        l->ult = no;
    }else{
        l->ult->prox = no;
        l->ult = no;
    }

    l->tam++;

    return 1;
}

/* Remove e retorna o primeiro nodo da lista. */
nodo *removeL(struct lista *l){
    struct nodo *aux;

    /* Remoção do Nodo e 
     * reposicionamento de ponteiros. */
    aux = l->prime;
    l->prime = aux->prox;
    l->tam--;

    if(listaVazia(l))
        l->ult = NULL;

    return aux;
}

/* Destroi a lista inteira, liberando memória. */
lista *destroiLista(struct lista *l){
    struct nodo *aux, *no;

    if(!l) return NULL;

    /* Percorre a lista liberando memória. */
    aux = l->prime;
    while(aux != NULL){
        no = aux->prox;
        free(aux->string);
        free(aux);
        aux = no;
    }

    free(l);
    
    return NULL;
}

/* Imprime todas as strings da lista. */
void imprimeStrings(struct lista *l){
    struct nodo *aux;

    if(!l) return;

    /* Percorre a lista e imprime as strings. */
    aux = l->prime;
    while(aux != NULL){
        printf("Qtd: %d ", aux->ind);
        printf("%s\n", aux->string);
        aux = aux->prox;
    }

    return;
}