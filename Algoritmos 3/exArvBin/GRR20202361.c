/*---------------------------------------------------------
PROGRAMA: cliente TAD ArvBin
-----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

typedef int ItemArv;
#include "arvBin.h"

/* ------------------------------------------------------*/
/* Funções para a lista de exercícios  */

void escreve(ArvBin a, ArvBin b){
    
    b->item = a->item;
}

void troca(ArvBin a, ArvBin b){
    int aux;

    aux = a->item;
    a->item = b->item;
    b->item = aux;
}

int somaChave(ArvBin arv){
    if(arvVazia(arv)) return 0;

    return arv->item + somaChave(arv->esq) + somaChave(arv->dir);
}

/* Retorna o menor item entre duas árvores. */
int menor(ArvBin p, ArvBin f){
    if(p->item < f->item) return p->item;

    return f->item;
}

int valorMinimo(ArvBin arv){
    if(arvVazia(arv)) return 0;

    /* Retorna o nodo caso seja folha. */
    if((arv->esq == NULL) && (arv->dir == NULL))
        return arv->item;

    if(arv->esq == NULL){
        return menor(arv, arv->dir);
    }

    if(arv->dir == NULL){
        return menor(arv, arv->esq);
    }

    int m1, m2, min;
    min = arv->item;

    /* Chamada recursiva para os nodos inferiores. */
    m1 = valorMinimo(arv->esq);
    m2 = valorMinimo(arv->dir);

    /* Lógica para calcular o menor. */
    if(m1 < min)
        min = m1;
    if(m2 < min)
        min = m2;

    return min;
}   

ArvBin paiMaior(ArvBin arv){
    if(arvVazia(arv)) return NULL;

    if((arv->esq == NULL) && (arv->dir == NULL))
        return arv;

    int m;
    m = arv->item;

    /* Chamadas recursivas. */
    arv->esq = paiMaior(arv->esq);
    arv->dir = paiMaior(arv->dir);

    /* Se o filho for maior que o pai.
     * escreve o valor do filho no pai. */
    if(arv->esq != NULL){
        if(arv->esq->item > m)
            escreve(arv->esq, arv);
    }
    if(arv->dir != NULL){
        if(arv->dir->item > m)
            escreve(arv->dir, arv);
    }

    return arv;
}

ArvBin maiorNaRaiz(ArvBin arv){
    if(arvVazia(arv)) return NULL;

    if((arv->esq == NULL) && (arv->dir == NULL))
        return arv;

    int m, aux;
    m = arv->item;

    /* Chamadas recursivas. */
    arv->esq = maiorNaRaiz(arv->esq);
    arv->dir = maiorNaRaiz(arv->dir);

    /* Se o filho for maior que o pai
     * efetua a troca de itens. */
    if(arv->esq != NULL){
        if(arv->esq->item > m)
            troca(arv->esq, arv);
    }
    if(arv->dir != NULL){
        if(arv->dir->item > m)
            troca(arv->dir, arv);
    }

    return arv;
}

ArvBin concerta(ArvBin arv){

    return maiorNaRaiz(arv);
}

ArvBin ordenaPeloMaior(ArvBin arv){
    if(arvVazia(arv)) return NULL;

    if((arv->esq == NULL) && (arv->dir == NULL))
        return arv;

    int m, aux;
    m = arv->item;

    /* Chamadas recursivas. */
    arv->esq = ordenaPeloMaior(arv->esq);
    arv->dir = ordenaPeloMaior(arv->dir);

    /* Efetua a troca se o filho for maior 
     * e chama a função para concertar sub-árvore. */
    if(arv->esq != NULL){
        if(arv->esq->item > m){
            troca(arv->esq, arv);
            arv->esq = concerta(arv->esq);
        }
    }
    if(arv->dir != NULL){
        if(arv->dir->item > m){
            troca(arv->dir, arv);
            arv->dir = concerta(arv->dir);
        }
    }

    return arv;
}

ArvBin dobraArvore(ArvBin arv){
    if(arvVazia(arv)) return NULL;

    /* Chamadas recursivas. */
    arv->esq = dobraArvore(arv->esq);
    arv->dir = dobraArvore(arv->dir);

    int n;
    ArvBin pai;

    /* Alocalção de memória. */
    pai = malloc(sizeof(Nodo));
    if(!pai) return NULL;
    n = arv->item;

    /* Lógica par-ímpar para 
     * o item do pai. */
    if(n % 2){
        pai->item = n - 1;
        pai->dir = arv;
        pai->esq = NULL;
    }else{
        pai->item = n + 1;
        pai->esq = arv;
        pai->dir = NULL;
    }

    return pai;
}
 

/* ----------------------------------------------------- */
/* Programa: cria uma árvore binária e imprime a árvore
*/
int main(int argc, char *argv[]){
  ArvBin arv;
  ItemArv v;

  criaArv( &arv );
  printf("Insira uma sequencia de chaves. Finalize a sequencia com 0: \n");
  scanf( "%d", &v );
  while( v != 0 ){
    insereArvNivel( v, &arv );
    scanf( "%d", &v );
  }
  printf( "\nArvore\n" );
  escreveArv( arv );

  /*----   chamada das funcoes da lista ---- */
  /* O programa padrão apresenta vazamentos de memória.
   * As funções funcionam corretamente apesar do
   * escreveArv não imprimir a árvore de forma 
   * horizontal. */

  printf("%d\n", somaChave(arv));

  printf("%d\n", valorMinimo(arv));

  arv = paiMaior(arv);
  escreveArv( arv );

  arv = maiorNaRaiz(arv);
  escreveArv(arv);

  arv = ordenaPeloMaior(arv);
  escreveArv(arv);

  arv = dobraArvore(arv);
  escreveArv(arv);

  /*--------------------------------------------- */

  free( arv );
  return 0;
}
