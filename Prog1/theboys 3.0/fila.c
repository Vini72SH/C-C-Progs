#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/* 
 * Cria e retorna uma nova fila.
 * Retorna NULL em caso de erro de alocação.
*/
struct fila *fila_cria (){
    struct fila *Nova_Fila;

    Nova_Fila = malloc(sizeof(struct fila));
    if (Nova_Fila == NULL){
        return NULL;
    }

    /* Inicialização da fila. */
    Nova_Fila->ini = NULL;
    Nova_Fila->fim = NULL;
    Nova_Fila->tamanho = 0;

    return Nova_Fila;
}

/* Desaloca toda memoria da fila e faz fila receber NULL. */
void fila_destroi (struct fila **fila){
    int d;

    if(*fila){
        /* Percorre a fila liberando memória. */
        while(!(fila_vazia(*fila))){
            dequeue(*fila, &d);
        }
        free(*fila);
        *fila = NULL;
    }
}

/* 
 * Insere dado na fila (politica FIFO). Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int enqueue (struct fila *fila, int dado){
    struct nodo *Novo_Nodo;
    
    if(fila == NULL){
        return 0;
    }

    /* Alocação do Nodo. */
    Novo_Nodo = malloc(sizeof(struct nodo));
    if(Novo_Nodo == NULL){
        return 0;
    }

    /* Atribuição dos valores. */
    Novo_Nodo->chave = dado;
    Novo_Nodo->prox = NULL;

    /* Algoritmo para caso a fila esteja vazia
     * ou não. */
    if(fila_vazia(fila)){
        /* Insere o elemento no começo da fila. */
        fila->ini = Novo_Nodo;
        fila->fim = Novo_Nodo;
    }else{
        /* Insere o elemento no fim da fila. */
        fila->fim->prox = Novo_Nodo;
        fila->fim = Novo_Nodo;
    }

    fila->tamanho++;

    return 1;
}

/* 
 * Remove dado da fila (politica FIFO) e retorna o elemento 
 * no parametro dado. A funcao retorna 1 em caso de 
 * sucesso e 0 no caso da fila estar vazia.
*/
int dequeue (struct fila *fila, int *dado){
    struct nodo *aux;

    if((fila == NULL) || (fila_tamanho(fila) == 0)){
        return 0;
    }

    /* Remoção do primeiro elemento da fila. */
    *dado = fila->ini->chave;
    aux = fila->ini;
    fila->ini = fila->ini->prox;

    free(aux);
    fila->tamanho--;

    return 1;
}
 
/* Retorna o numero de elementos da pilha, que pode ser 0. */
int fila_tamanho (struct fila *fila){
    if(fila != NULL){
        return fila->tamanho;    
    }
    
    return -1;
}

/* Retorna 1 se fila vazia, 0 em caso contrario. */ 
int fila_vazia (struct fila *fila){
    if (fila != NULL){
        if (fila_tamanho(fila) == 0){
            return 1;
        }else{
            return 0;
        }
    }

    return 1;
}

/* Imprime a fila no formato "[ e1 e2 ... en ]" 
 * Se a fila for vazia imprime "[ ]" */
void fila_imprime (struct fila *fila){
    struct nodo* aux;

    if(fila == NULL){
        return;
    }

    /* Impressão da fila. */
    aux = fila->ini;
    printf("[ ");
    while(aux != NULL){
        printf("%d ", aux->chave);
        aux = aux->prox;
    }
    printf("]\n");

    return;
}