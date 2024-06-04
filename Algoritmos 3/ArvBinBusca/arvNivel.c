/*---------------------------------------------------------
PROGRAMA: cliente TAD ArvBin que escreve os itens em uma árvore binária
por nível. Utiliza o TAD Fila.
-----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

typedef int ItemArv;
#include "arvBin.h"

typedef ArvBin ItemFila;
#include "fila.h"

/* ----------------------------------------------------- */
/* Escreve os itens armazenados na árvore por nível */
void percorrePorNivel( ArvBin p ){
  Fila f;
  ArvBin nodo;

  criaFila( &f );
  insereFila( p, &f );
  while( !filaVazia( f )){
    removeFila( &f, &nodo );
    if( nodo!= NULL ){
      printf("%d\n", nodo->item );
      insereFila( nodo->esq, &f );
      insereFila( nodo->dir, &f );
    }
  }
}

/* ----------------------------------------------------- */
/* Programa: cria uma árvore binária e imprime a árvore
*/
int main(int argc, char *argv[]){
  ArvBin arv;
  ItemArv v;
  
  criaArv( &arv );
  scanf( "%d", &v );
  while( v != 0 ){
    arv= insereArv( v, arv );
    scanf( "%d", &v );
  }
  printf( "\nArvore\n" );
  escreveArv( arv );

  percorrePorNivel( arv );
  freeArv( arv );
  return 0;
}
