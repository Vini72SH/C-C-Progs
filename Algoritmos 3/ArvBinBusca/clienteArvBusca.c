/*---------------------------------------------------------
PROGRAMA: cliente TAD ArvBusca
-----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

typedef int ItemArv;
#include "itemInt.h"
#include "arvBusca.h"

/* ----------------------------------------------------- */
/* Programa: cria uma árvore binária e imprime a árvore
*/
void escreveValor( ItemArv v ){
  write( v );
  printf("\n");
}

int main(int argc, char *argv[]){
  ArvBusca arv, apNodo;
  ItemArv v;
  int k;
  
  criaArv( &arv );
  read( v );
  while( !eq( v, FIM )){
    arv= insereArv( v, arv );
    read( v );
  }
  printf( "\nArvore\n" );
  escreveArv( arv );

  printf( "\nValores ordenados\n" );
  visitaOrdenado( arv, &escreveValor );

  /*
  printf("\nEntre com a ordem do elemento (k): " );
  scanf( "%d", &k );
  apNodo= buscaElementoK( k, arv );
  if( apNodo != NULL )
    escreveValor( apNodo->item );
  
  printf("\nEntre com o valor do elemento: " );
  read( v );
  apNodo= buscaArv( v, arv );
  if( apNodo != NULL )
    printf("Valor encontrado\n" );
  else
    printf( "Valore nao encontrado\n" );

  */

  printf("Digite o valor para inserir na raiz: ");
  scanf("%d", &k);

  printf("\n");
  arv = insereNaRaiz(k, arv);
  escreveArv(arv);

  freeArv( arv );

  return 0;
}
