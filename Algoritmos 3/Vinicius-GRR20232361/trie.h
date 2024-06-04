#ifndef __TRIE__
#define __TRIE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "lista.h"

#define NUMCHARACTERS 39
#define LINESIZE 1024
#define CHARS "\0 0123456789abcdefghijklmnopqrstuvwxyz?"

typedef struct Nodo *ApNodo;
typedef struct Nodo{
    char *prefix;
    char characters[NUMCHARACTERS];
    ApNodo prox[NUMCHARACTERS];
}Nodo;
typedef ApNodo Trie;

char *padronizaString(char *entrada);
void criaArv(Trie *raiz);
void freeArv(Trie raiz);
Trie insere(char *string, Trie raiz);
Trie busca(Trie raiz, char *string, short dig);
void imprimePrefix(Trie raiz, char *prefix);
void imprimeMaior(Trie raiz, char *prefix, short dig);
void filtroTitulos(lista *l, char **comands, int tam);
void functionUnity(Trie raiz, char *string);
void escreve(Trie raiz);

#endif