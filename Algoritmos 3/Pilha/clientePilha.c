/*---------------------------------------------------------
PROGRAMA: cliente TAD pilha
-----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

typedef char ItemPilha[50];
#include "pilha.h"
#include "itemString.h"

/* ----------------------------------------------------- 
  Programa: cria uma pilha e escreve os seus valores
*/
int main(int argc, char *argv[]){
  Pilha pilha;
  ItemPilha v;
  
  criaPilha( &pilha );
  read( v );
  while( !eq( v, FIM )){
    empilha( v, &pilha );
    read( v );
  }
  printf( "\nPilha\n" );
  while( !pilhaVazia( pilha )){
    desempilha( &pilha, &v );
    write( v );
    printf("\n");
  }
  return 0;
}

