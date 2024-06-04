#include "lista.h"

lista *criaLista (){
    lista *l;

    l = malloc(sizeof(lista));
    if (!l) return NULL;

    l->tam = 0;
    l->prime = NULL;
    l->ult = NULL;

    return l;
}

int listaVazia(lista *l){
    if(!l) return 0;

    if(l->tam == 0) return 1;
    
    return 0;
}

struct nodo *criaNo (char *s){
    struct nodo *novo;

    novo = malloc(sizeof(struct nodo));
    if(!novo) return NULL;

    strcpy(novo->string, s);
    novo->prox = NULL;

    return novo;
}

int insereL(lista *l, char *s){
    struct nodo *aux, *no;

    if(!l) return 0;

    aux = l->prime;
    while((aux != NULL) && ((strcmp(s, aux->string)) != 0)){
        aux = aux->prox;
    }

    if(aux != NULL)
        return 1;

    no = criaNo(s);
    if(!no) return 0;
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

struct nodo *removeL(lista *l, char *s){
    struct nodo *aux, *no;

    if(!(l)) return NULL;

    aux = l->prime;
    if((l->prime != NULL) && (strcmp(l->prime->string, s) == 0)){
        no = l->prime;
    }else{
        while((aux->prox) && (strcmp(aux->prox->string, s) != 0))
            aux = aux->prox;
        no = aux->prox;
    }

    if(!(no)) return NULL;

    if(no == l->prime)
        l->prime = no->prox;
    else
        aux->prox = no->prox;

    if(no == l->ult)
        l->ult = NULL;

    l->tam--;

    return no;
}

lista *destroiLista(lista *l){
    struct nodo *aux, *no;

    if(!l) return NULL;

    aux = l->prime;
    while(aux != NULL){
        no = aux->prox;
        free(aux);
        aux = no;
    }

    free(l);
    
    return NULL;
}

void imprimePalavras(lista *l){
    struct nodo *aux;

    if(!l) return;

    aux = l->prime;
    while(aux != NULL){
        printf("%s\n", aux->string);
        aux = aux->prox;
    }

    return;
}