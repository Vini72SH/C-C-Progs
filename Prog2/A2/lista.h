#ifndef __lista__
#define __lista__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo{
    int ind;
    char *string;
    struct nodo *prox;
}nodo;

typedef struct lista{
    int tam;
    struct nodo *prime;
    struct nodo *ult;
}lista;

/* Cria a lista / Retorna um ponteiro. */
lista *criaLista ();

/* Retorna 1 se a lista está vazia. */
int listaVazia(struct lista *l);

/* Cria nodo e insere a string s e o indice i. 
 * Retorna um ponteiro para o nodo. */
nodo *criaNodo (char *s, int i);

/* Insere na lista a string s com indice ind 
 * Retorna 1 caso seja bem sucedido. */
int insereL(struct lista *l, char *s, int ind);

/* Remove o primeiro nodo da lista 
 * e retorna um ponteiro para esse nodo. */
nodo *removeL(struct lista *l);

/* Percorre toda a lista, liberando memória
 * e retorna NULL. */
lista *destroiLista(struct lista *l);

/* Imprime todas as strings da lista. */
void imprimeStrings(struct lista *l);

#endif