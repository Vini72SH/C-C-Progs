#include <stdlib.h>
#include <stdio.h>
#include "lef.h"

struct evento_t *cria_evento (int tempo, int tipo, int dado1, int dado2){
    struct evento_t *Novo_Evento;

    /* Alocação de Memória. */
    Novo_Evento = malloc(sizeof(struct evento_t));
    if(Novo_Evento == NULL){
        return NULL;
    }

    /* Atribuição de Variáveis. */
    Novo_Evento->tempo = tempo;
    Novo_Evento->tipo = tipo;
    Novo_Evento->dado1 = dado1;
    Novo_Evento->dado2 = dado2;

    return Novo_Evento;
}

/* 
 * Destroi um evento e retorna NULL.
 */ 
struct evento_t *destroi_evento (struct evento_t *e){

    if(e != NULL){
        free(e);
    }

    return NULL;
}

struct lef_t *cria_lef (){
    struct lef_t *Nova_Lef;

    /* Alocação de Memória. */
    Nova_Lef = malloc(sizeof(struct lef_t));
    if(Nova_Lef == NULL){
        return NULL;
    }

    Nova_Lef->primeiro = NULL;

    return Nova_Lef;
}

struct lef_t *destroi_lef (struct lef_t *l){
    struct evento_t *e;
    struct nodo_lef_t *aux, *no;

    /* Percorre a LEF liberando a memória. */
    if(l != NULL){
        aux = l->primeiro;
        while(aux != NULL){
            no = aux->prox;
            e = retira_lef(l);
            destroi_evento(e);
            free(aux);
            aux = no;
        }
    }

    free(l);

    return NULL;
}

int insere_lef (struct lef_t *l, struct evento_t *e){
    struct nodo_lef_t *aux;
    struct nodo_lef_t *Novo_Nodo;

    /* Alocação de Memória. */
    Novo_Nodo = malloc(sizeof(struct nodo_lef_t));
    if(Novo_Nodo == NULL){
        return 0;
    }

    /* Insere o evento na primeira posição. */
    Novo_Nodo->evento = e;
    if(vazia_lef(l) || e->tempo < l->primeiro->evento->tempo){
        Novo_Nodo->prox = l->primeiro;
        l->primeiro = Novo_Nodo;

        return 1;
    }

    /* Percorre a LEF buscando a posição correta. */
    aux = l->primeiro;
    while((aux->prox != NULL) && (aux->evento->tempo <= e->tempo)){
        aux = aux->prox;
    }

    Novo_Nodo->prox = aux->prox;
    aux->prox = Novo_Nodo;

    return 1;
}

/* 
 * Retira o primeiro evento da LEF.
 * Retorna ponteiro para o evento ou NULL se falhar.
 */
struct evento_t *retira_lef (struct lef_t *l){
    struct nodo_lef_t *aux;
    struct evento_t *evento;

    if((l == NULL) || (vazia_lef(l))){
        return NULL;
    }

    aux = l->primeiro;
    evento = aux->evento;
    l->primeiro = aux->prox;

    free(aux);

    return evento;
}

/* 
 * Informa se a LEF está vazia.
 * Retorna 1 se vazia e 0 senao ou se falhar.
 */
int vazia_lef (struct lef_t *l){

    if((l != NULL) && (l->primeiro == NULL)){

        return 1;
    }

    return 0;
}

/* Impressão da LEF. */
void imprime_lef (struct lef_t *l){
    int i;
    struct nodo_lef_t *aux;

    i = 0;
    aux = l->primeiro;
    while(aux != NULL){
        printf("%d ", aux->evento->tempo);
        printf("%d ", aux->evento->tipo);
        printf("%d ", aux->evento->dado1);
        printf("%d\n", aux->evento->dado2);
        aux = aux->prox;
        i++;
    }

    printf("total %2d eventos\n", i);
}