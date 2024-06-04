/*---------------------------------------------------------
Implementação: TAD Árvore Binária de Busca
-----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int ItemArv;
#include "itemInt.h"
#include "arvBusca.h"

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

void escreveNodo( ArvBusca p, int h ){
  if( p == NULL ){
    escreveNodoExterno( h );
    return;
  }
  escreveNodo( p->dir, h+1 );
  escreveNodoInterno( p->item, h );
  escreveNodo( p->esq, h+1 );
}

void escreveArv( ArvBusca arv ){
  escreveNodo( arv, 0 );
}

/* ----------------------------------------------------- */
/* Função de inicialização de uma árvore vazia */
void criaArv(ArvBusca *arv){
  *arv = NULL;
}

/* ----------------------------------------------------- */
/* Função que verifica se a árvore está vazia */
int arvVazia(ArvBusca arv){
  return (arv == NULL);
}

/* ----------------------------------------------------- */
/* Retorna a quantidade de nodos internos na arvore      */
int contaNoArv( ArvBusca p ){
    if( p == NULL )
        return 0;
    return p->n;
}

/* ----------------------------------------------------- */
/* Retorna a altura da arvore com raiz em p */
int alturaArv( ArvBusca p ){
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
int arvCompleta( ArvBusca arv ){
  if( contaNoArv( arv ) == pow(2, alturaArv(arv))-1 )
    return 1;
  return 0;
}

/* ----------------------------------------------------- */
/* Criação de um novo nodo com o valor do Item preenchido com v */
ArvBusca criaNoArv( ItemArv v, ArvBusca esq, ArvBusca dir, int n ){
  ArvBusca p;

  p = (ArvBusca)malloc( sizeof(Nodo) );
  cp(p->item, v); p->esq = esq; p->dir = dir; p->n= n;
  return p;
}

/* ----------------------------------------------------- 
/* Insere um novo Item na árvore como folha */
ArvBusca insereArv( ItemArv v, ArvBusca arv ){
  if( arvVazia( arv ))
    return criaNoArv( v, NULL, NULL, 1 );
  (arv->n)++;
  if( lt( v, arv->item ))
    arv->esq= insereArv( v, arv->esq );
  else
    arv->dir= insereArv( v, arv->dir );
  return arv;
}

/* ----------------------------------------------------- 
/* Insere um novo Item na árvore como folha - função iterativa */
ArvBusca insereArvIterativo( ItemArv v, ArvBusca raiz ){
  ArvBusca p, pai;
  
  if( arvVazia( raiz ))
    return criaNoArv( v, NULL, NULL, 1 );
  p= raiz;
  while( p != NULL ){
    pai= p;
    (p->n)++;
    if( lt( v, p->item ))
      p= p->esq;
    else
      p= p->dir;
  }
  if( lt( v, pai->item))
    pai->esq= criaNoArv( v, NULL, NULL, 1 );
  else
    pai->dir= criaNoArv( v, NULL, NULL, 1 );
  return raiz;
}      


/* -----------------------------------------------------*/
/* Busca o  nodo que contem uma chave como Item */
ArvBusca buscaArv( ItemArv v, ArvBusca p ){
    if(!p){
        return NULL;
    }

    if(eq(v, p->item)) return p;

    if(lt(v, p->item)) return buscaArv(v, p->esq);
    
    return buscaArv(v, p->dir);
}        
 

/* ----------------------------------------------------- */
/* Libera espaço alocado para toda a árvore              */
void freeArv( ArvBusca p ){
  if( p != NULL ){
    freeArv( p->esq );
    freeArv( p->dir );
    free( p );
  }
}

/* ----------------------------------------------------- */
/* Busca a nodo com a k-ésima chave no árvore            */
 
ArvBusca buscaElementoK( int k, ArvBusca p ){
    int contaEsq;

    if(!p) return NULL;

    contaEsq = (!p->esq)?0: p->esq->n;
    if(contaEsq == k){
        return p;
    }else if(k <= contaEsq){
        return buscaElementoK(k, p->esq);
    }else{
        return buscaElementoK(k - contaEsq - 1, p->dir);
    }
}

/* ----------------------------------------------------- */
/* Visita a árvore de forma ordenada                     */

void visitaOrdenado( ArvBusca p, void (*funcao)(Item) ){
    if(p == NULL){
        return;
    }

    visitaOrdenado(p->esq, funcao);
    funcao(p->item);
    visitaOrdenado(p->dir, funcao);

    return;
}

/* Atualiza o N de todos os nodos da árvore p */
int atualizaN(ArvBusca p){
    if(p == NULL) return 0;

    return 1 + atualizaN(p->esq) + atualizaN(p->dir);
}

/* ----------------------------------------------------- */
/* Rotaciona um nodo para a direita                      */
ArvBusca rotacaoDir(ArvBusca p){
    ArvBusca esqP;

    esqP = p->esq; p->esq = esqP->dir; esqP->dir = p;

    esqP->n = atualizaN(esqP);
    p->n = atualizaN(p);

    return esqP;
}

/* ----------------------------------------------------- */
/* Rotaciona um nodo para a esquerda                     */
ArvBusca rotacaoEsq(ArvBusca p){
    ArvBusca dirP;

    dirP = p->dir; p->dir = dirP->esq; dirP->esq = p;

    dirP->n = atualizaN(dirP);
    p->n = atualizaN(p);

    return dirP;
}

ArvBusca particaoR(int k, ArvBusca p){
    int contaEsq;

    contaEsq = (p->esq == NULL)?0:p->esq->n;
    if(k == contaEsq){
        return p;
    }else if(k <= contaEsq){
        p->esq = particaoR(k, p->esq);
        return rotacaoDir(p);
    }else{
        p->dir = particaoR(k - contaEsq - 1, p->dir);
        return rotacaoEsq(p);
    }
}

ArvBusca insereNaRaiz(ItemArv v, ArvBusca arv){
    if(arv == NULL){
        return criaNoArv(v, NULL, NULL, 1);
    }

    if(lt(v, arv->item)){
        arv->esq = insereNaRaiz(v, arv->esq);
        arv = rotacaoDir(arv);
    }

    if(gt(v, arv->item)){
        arv->dir = insereNaRaiz(v, arv->dir);
        arv = rotacaoEsq(arv);
    }

    return arv;
}

ArvBusca particao(int k, ArvBusca raiz){
    if(raiz->n < k){
        return raiz;
    }

    return particaoR(k, raiz);
}

ArvBusca juntaEsqDir (ArvBusca e, ArvBusca d){
    if(!d) return e;
    d = particao(1, d);
    d->esq = e;
    return d;
}

ArvBusca removeArv(ItemArv v, ArvBusca p){
    ArvBusca NodoV;

    if(p == NULL) return p;
    if(lt(v, p->item)){
        p->esq = removeArv(v, p->esq);
    }else if(gt(v, p->item)){
        p->dir = removeArv(v, p->dir);
    }else{
        NodoV = p;
        p = juntaEsqDir(p->esq, p->dir);
        free(NodoV);
    }

    return p;

}

ArvBusca juntaArv(ArvBusca r1, ArvBusca r2){
    if(r2 == NULL) return r1;
    if(r1 == NULL) return r2;
    r2 = insereNaRaiz(r1->item, r2);
    r2->esq = juntaEsqDir(r1->esq, r2->esq);
    r2->dir = juntaEsqDir(r1->dir, r2->dir);
    free(r1);

    return r2;
}