#include <stdio.h>
#include <stdlib.h>
#include "lef.h"

/*Cria um novo evento.*/
struct evento_t *cria_evento (int tempo, int tipo, int dado1, int dado2){
    struct evento_t *novoEvento;

    /*Alocação de Memória*/
    novoEvento = malloc(sizeof(struct evento_t));
    if (novoEvento == NULL){
        return NULL;
    }

    /*Atribuição dos valores.*/
    novoEvento->tempo = tempo;
    novoEvento->tipo = tipo;
    novoEvento->dado1 = dado1;
    novoEvento->dado2 = dado2;

    return novoEvento;
}

struct evento_t *destroi_evento (struct evento_t *e){

    /*Verifica se o evento existe.*/
    if(e != NULL){
        free(e);
    }

    return NULL; 
}

struct lef_t *cria_lef (){
    struct lef_t *novaLef;

    /*Alocação de Memória.*/
    novaLef = malloc(sizeof(struct lef_t));
    if(novaLef == NULL){
        return NULL;
    }

    /*Define a LEF com vazia.*/
    novaLef->primeiro = NULL;

    return novaLef;
}

struct lef_t *destroi_lef (struct lef_t *l){
    struct evento_t *evento;
    struct nodo_lef_t *aux, *no;

    /*Percorre a LEF, liberando a memória dos nodos e
     eventos. Por fim, destrói a LEF.*/
    if(l != NULL){
        aux = l->primeiro;
        while(aux != NULL){
            no = aux->prox;
            evento = aux->evento;
            destroi_evento(evento);
            free(aux);
            aux = no;
        }

        free(l);
    }

    return NULL;
}

int insere_lef (struct lef_t *l, struct evento_t *e){
    struct nodo_lef_t *novoNodo, *aux;

    novoNodo = malloc(sizeof(struct nodo_lef_t));
    if(novoNodo == NULL){
        return 0;
    }

    novoNodo->evento = e;

    /*Caso o novo evento tenha tempo menor que o primeiro
    ou a LEF estar vazia, insere na primeira posição.*/
    if (vazia_lef(l) || novoNodo->evento->tempo < l->primeiro->evento->tempo){
        novoNodo->prox = l->primeiro;
        l->primeiro = novoNodo;

        return 1;
    }

    aux = l->primeiro;
    while((aux->prox != NULL) && (aux->prox->evento->tempo <= novoNodo->evento->tempo)){
        aux = aux->prox;
    }

    novoNodo->prox = aux->prox;
    aux->prox = novoNodo;

    return 1;
}

struct evento_t *retira_lef (struct lef_t *l){
    struct nodo_lef_t *aux;
    struct evento_t *evento;

    /*Se não houver LEF ou evento, retorna NULL.*/
    if((l == NULL) || vazia_lef(l)){
        return NULL;
    }

    /*Retira o primeiro nodo e retorna o evento.*/
    aux = l->primeiro;
    evento = aux->evento;
    l->primeiro = aux->prox;

    free(aux);

    return evento;
}

/*Informa se a LEF está vazia.*/
int vazia_lef (struct lef_t *l){
    if(l->primeiro == NULL){
        return 1;
    }

    return 0;
}

/*Imprime os eventos da LEF e a quantidade deles.*/
void imprime_lef (struct lef_t *l){
    int cont = 0; 
    struct nodo_lef_t *aux;

    printf("LEF:\n");
    if(!(vazia_lef(l))){
        aux = l->primeiro;
        while(aux != NULL){
            cont++;
            printf("  tempo %d tipo %d d1 %d d2 %d\n", aux->evento->tempo, aux->evento->tipo, aux->evento->dado1, aux->evento->dado2);
            aux = aux->prox;
        }
    }
    printf("  Total %d eventos\n", cont);
}