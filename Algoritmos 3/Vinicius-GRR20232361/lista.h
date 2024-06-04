#ifndef __LISTA___
#define __LISTA___

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
    char string[1024];
    struct nodo *prox;
};

typedef struct lista{
    int tam;
    struct nodo *prime;
    struct nodo *ult;
}lista;

lista *criaLista ();
int listaVazia(lista *l);
struct nodo *criaNo (char *s);
int insereL(lista *l, char *s);
struct nodo *removeL(lista *l, char *s);
lista *destroiLista(lista *l);
void imprimePalavras(struct lista *l);

#endif