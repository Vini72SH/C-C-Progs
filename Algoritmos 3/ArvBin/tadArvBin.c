/*---------------------------------------------------------
Implementação: TAD Árvore
-----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int ItemArv;
#include "itemInt.h"
#include "arvBin.h"

/* ----------------------------------------------------- */
/* Impressão da árvore */
void escreveNodoInterno( ItemArv v, int h ){
  int i;

  for( i=0; i<h; i++ )
    printf( "   " );
  write( v );
  printf( "\n" );
}

void escreveNodoExterno( int h ){
  int i;

  for( i=0; i<h; i++ )
    printf( "   " );
  printf( "*\n" );
}

void escreveNodo( ArvBin p, int h ){
  if( p == NULL ){
    escreveNodoExterno( h );
    return;
  }
  escreveNodo( p->dir, h+1 );
  escreveNodoInterno( p->item, h );
  escreveNodo( p->esq, h+1 );
}

void escreveArv( ArvBin arv ){
  escreveNodo( arv, 0 );
}

/* ----------------------------------------------------- */
/* Função de inicialização de uma árvore vazia */
void criaArv(ArvBin *arv){
  *arv = NULL;
}

/* ----------------------------------------------------- */
/* Função que verifica se a árvore está vazia */
int arvVazia(ArvBin arv){
  return (arv == NULL);
}

/* ----------------------------------------------------- */
/* Retorna a quantidade de nodos internos na arvore      */
int contaNoArv( ArvBin p ){
    if( p == NULL )
        return 0;
    return 1 + contaNoArv( p-> esq ) + contaNoArv( p->dir );
}

/* ----------------------------------------------------- */
/* Retorna a altura da arvore com raiz em p */
int alturaArv( ArvBin p ){
    int he, hd;

    if( p == NULL )
        return 0;
    he= alturaArv( p-> esq );
    hd= alturaArv( p->dir );
    if( he > hd )
        return he+1;
    else
        return hd+1;
}


/* ----------------------------------------------------- 
   Verifica se a árvore está completa
*/
int arvCompleta( ArvBin arv ){
  if( contaNoArv( arv ) == pow(2, alturaArv(arv))-1 )
    return 1;
  return 0;
}

/* ----------------------------------------------------- */
/* Criação de um novo nodo com o valor do Item preenchido com v */
ArvBin criaNoArv( ItemArv v ){
  ArvBin p;

  p = (ArvBin)malloc( sizeof(Nodo) );
  cp(p->item, v); p->esq = NULL; p->dir = NULL;
  return p;
}

/* ----------------------------------------------------- 
/* Insere um novo Item na árvore */
ArvBin insereArv( ItemArv v, ArvBin arv ){
  ArvBin p;

  if( arvVazia( arv ))
    return criaNoArv( v );
  if( leq(v, arv->item ))
    arv->esq= insereArv( v, arv->esq );
  else
    arv->dir= insereArv( v, arv->dir );
  return arv;
}

/* ----------------------------------------------------- */
/* Libera espaço alocado para toda a árvore              */
void freeArv( ArvBin p ){
  if( p != NULL ){
    freeArv( p->esq );
    freeArv( p->dir );
    free( p );
  }
}


