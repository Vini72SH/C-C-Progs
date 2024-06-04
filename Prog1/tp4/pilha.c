#include "pilha.h"
#include <stdlib.h>

struct pilha *pilha_cria (){
	struct pilha *p;

	/*Aloca a memória para a pilha*/
    p = malloc(sizeof(struct pilha));

    if (p == NULL){
        return NULL;
    }

    /*Inicializa a pilha.*/
    p->topo = NULL;
    p->tamanho = 0;

    return p;
}

/* Desaloca toda memoria da pilha e faz pilha receber NULL. */
void pilha_destroi (struct pilha **pilha){
	struct nodo *no, *aux;

    /*Verifica se a pilha não é nula*/
    if (*pilha){
        aux = (*pilha)->topo;
        while(aux != NULL){
        	/*Percorre a pilha, liberando memória*/
            no = aux->prox;
            free(aux);
            aux = no;
        }
        free(*pilha);
        (*pilha) = NULL;
    }
}

int push (struct pilha *pilha, int dado){
	struct nodo *novo;

    novo = malloc(sizeof(struct nodo));
    if(novo == NULL){
        return 0;
    }

    /*Adiciona  elemento no topo da pilha.*/
    novo->chave = dado;
    novo->prox = pilha->topo;
    pilha->topo = novo;

    pilha->tamanho++;

    return 1;
}

int pop (struct pilha *pilha, int *dado){
	struct nodo *aux;

    if ((pilha == NULL) || (pilha_tamanho(pilha) == 0)){
        return 0;
    }

    /*Remove o elemento do topo da pilha.*/
    aux = pilha->topo;
    (*dado) = aux->chave;
    pilha->topo = aux->prox;

    free(aux);

    pilha->tamanho--;

    return 1;
}

int pilha_topo (struct pilha *pilha, int *dado){
	struct nodo *aux;

    if((pilha == NULL) || (pilha_tamanho(pilha) == 0)){
        return 0;
    }

    /*Mostra o elemento do topo da pilha*/
    aux = pilha->topo;
    (*dado) = aux->chave;

    return 1;
}

/*Retorna o numero de elementos da pilha*/
int pilha_tamanho (struct pilha *pilha){

	return pilha->tamanho;
}
 
int pilha_vazia (struct pilha *pilha){
	if(pilha->tamanho == 0){
        return 1;
    }

    return 0;
}