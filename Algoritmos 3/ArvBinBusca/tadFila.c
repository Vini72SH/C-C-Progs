/*---------------------------------------------------------
IMPLEMENTAÇÃO: TAD Fila
-----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

typedef float ItemFila;
#include "itemFloat.h"
#include "fila.h"

/* ----------------------------------------------------- */
/* Função de inicialização de uma pilha vazia 
*/
void criaFila( Fila *fila){
  fila->prim = NULL;
  fila->ult = NULL;
}

/* ----------------------------------------------------- 
  Criação de um novo nodo com o valor do Item preenchido com v 
*/
ApNoFila criaNoFila( ItemFila v ){
  ApNoFila p;

  p = (ApNoFila) malloc( sizeof(NoFila) );
  cp(p->item, v); p->prox = NULL;
  return p;
}

/* ----------------------------------------------------- 
   Retorna 1 se a fila estiver vazia e 0, caso contrario
*/
int filaVazia( Fila p ){
    if( p.prim == NULL )
        return 1;
    return 0;
}

/* ----------------------------------------------------- 
   Insere um novo Item na Fila 
*/
void insereFila( ItemFila v, Fila *fila ){
  ApNoFila p;
  
  p= criaNoFila( v );
  if( fila->prim == NULL ){
    fila->prim= p;
    fila->ult= p;
  }
  else{
    fila->ult->prox= p;
    fila->ult= p;
  }
}

/* ----------------------------------------------------- 
   Remove o primeiro Item da fila 
*/
void removeFila( Fila *fila, ItemFila *v){
  ApNoFila p;
  
  if( filaVazia( *fila ))
    cp( *v, ERRO);
  else{
    p= fila->prim;
    cp(*v, p->item);
    fila->prim= p->prox;
    free( p );
  }
}



