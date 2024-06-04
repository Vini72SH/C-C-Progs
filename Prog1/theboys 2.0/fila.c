#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

struct fila *fila_cria (){
   struct fila *nova_fila;

   /*Alocação de Memória para a fila.*/
   nova_fila = malloc(sizeof(struct fila));

   if(nova_fila == NULL){
      return NULL;
   }

   /*Inicialização da fila.*/
   nova_fila->ini = NULL;
   nova_fila->fim = NULL;
   nova_fila->tamanho = 0;

   return nova_fila;
}

/* Desaloca toda memoria da fila e faz fila receber NULL. */
void fila_destroi (struct fila **fila){
   struct nodo *no, *aux;

   if(*fila){
   	aux = (*fila)->ini;
   	/*Percorre a fila liberando memória*/
      while (aux != NULL){
         no = aux->prox;
         free(aux);
         aux = no;
         (*fila)->tamanho--;
      }
      free(*fila);
      *fila = NULL;
   }
}

/*Insere dado na fila (politica FIFO).*/
int enqueue (struct fila *fila, int dado){
   struct nodo *no;
   
   if(fila == NULL){
      return 0;
   }

   no = malloc(sizeof(struct nodo));
   if (no == NULL){
      return 0;
   }

   no->chave = dado;
   no->prox = NULL;

   /*Insere o elemento no primeiro lugar da fila.*/
   if(fila_vazia(fila)){
      fila->ini = no;
      fila->fim = no;
   }else{
   /*Insere o elemento no último lugar da fila.*/
      fila->fim->prox = no;
      fila->fim = no;
   }

   fila->tamanho++;

   return 1;
}

/* Remove dado da fila (politica FIFO).*/
int dequeue (struct fila *fila, int *dado){
   struct nodo *no;

   if(fila_vazia(fila)){
      return 0;
   }

   /*Remoção do primeiro da fila.*/
   no = fila->ini;
   *dado = no->chave;
   fila->ini = no->prox;
   free(no);

   fila->tamanho--;

   return 1;
}
 
/* Retorna o numero de elementos da pilha.*/
int fila_tamanho (struct fila *fila){

    return fila->tamanho;

}

/* Retorna 1 se a fila estiver vazia.*/ 
int fila_vazia (struct fila *fila){
    if(fila->tamanho == 0){
        return 1;
    }

   return 0;
}

void fila_imprime (struct fila *fila){
   struct nodo *aux;

   if(fila == NULL){
      return;
   }

   if(fila_vazia(fila)){
      printf("[ ]\n");
      return;
   }

   aux = fila->ini;
   printf("[ ");
   
   while(aux != NULL){
      printf("%d ", aux->chave);
      aux = aux->prox;
   }
   printf("]\n");
}