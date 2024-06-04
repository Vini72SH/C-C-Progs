/*--------------------------------------------------------- 
IMPLEMENTAÇÃO: TAD Pilha
-----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

typedef char ItemPilha[50];
#include "itemString.h"
#include "pilha.h"

/* ----------------------------------------------------- */
/* Função de inicialização de uma pilha vazia 
*/
void criaPilha(Pilha *pilha){
  *pilha = NULL;
}

/* ----------------------------------------------------- 
  Criação de um novo nodo com o valor do Item preenchido com v 
*/
Pilha criaNoPilha( ItemPilha v ){
  Pilha p;

  p = (Pilha)malloc( sizeof(NoPilha) );
  cp(p->item, v); p->prox = NULL;
  return p;
}

/* ----------------------------------------------------- 
   Retorna 1 se a pilha estiver vazia e 0, caso contrario
*/
int pilhaVazia( Pilha p ){
    if( p == NULL )
        return 1;
    return 0;
}

/* ----------------------------------------------------- 
   Empilha um novo Item 
*/
void empilha( ItemPilha v, Pilha *pilha ){
  Pilha p;
  
  p= criaNoPilha( v );
  p->prox= *pilha;
  *pilha= p;
}

/* ----------------------------------------------------- 
   Desempilha um Item 
*/
void desempilha( Pilha *pilha, ItemPilha *v){
  Pilha p;
  
  if( pilhaVazia( *pilha ))
    cp( *v, ERRO);
  else{
    p= *pilha;
    cp(*v, p->item);
    *pilha= p->prox;
    free( p );
  }
}



