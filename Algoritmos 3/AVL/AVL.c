/*---------------------------------------------------------
Implementação: TAD Árvore
-----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "AVL.h"

/* ----------------------------------------------------- */
/* Impressão da árvore */
void escreveNodoInterno( int v, int h ){
    int i;

    for( i=0; i<h; i++ )
        printf( "   " );
    printf("%d", v);
    printf( "\n" );
}

void escreveNodoExterno( int h ){
    int i;

    for( i=0; i<h; i++ )
        printf( "   " );
    printf( "*\n" );
}

void escreveNodo( ArvAVL p, int h ){
    if( p == NULL ){
        escreveNodoExterno( h );
        return;
    }
    escreveNodo( p->dir, h+1 );
    escreveNodoInterno( p->item, h );
    escreveNodo( p->esq, h+1 );
}

void escreveArv( ArvAVL arv ){
    escreveNodo( arv, 0 );
}

void ArvEmOrdem( ArvAVL arv){
    if(arvVazia(arv))
        return;

    ArvEmOrdem(arv->esq);
    printf("[%d] ", arv->item);
    ArvEmOrdem(arv->dir); 

}

void ArvPreOrdem( ArvAVL arv){
    if(arvVazia(arv))
        return;

    printf("[%d] ", arv->item);
    ArvPreOrdem(arv->esq);
    ArvPreOrdem(arv->dir); 

}
void ArvPosOrdem( ArvAVL arv){
    if(arvVazia(arv))
        return;

    ArvPosOrdem(arv->esq);
    ArvPosOrdem(arv->dir); 
    printf("[%d] ", arv->item);

}

/* ----------------------------------------------------- */
/* Função de inicialização de uma árvore vazia */
void criaArv(ArvAVL *arv){
    *arv = NULL;
}

/* ----------------------------------------------------- */
/* Função que verifica se a árvore está vazia */
int arvVazia(ArvAVL arv){
    return (arv == NULL);
}

/* ----------------------------------------------------- */
/* Retorna a quantidade de nodos internos na arvore      */
int contaNoArv( ArvAVL p ){
    if( p == NULL )
        return 0;
    return 1 + contaNoArv( p-> esq ) + contaNoArv( p->dir );
}

/* ----------------------------------------------------- */
/* Retorna a altura da arvore com raiz em p */
int alturaArv( ArvAVL p ){
    int he, hd;

    if( p == NULL )
        return 0;
    he = alturaArv( p->esq );
    hd = alturaArv( p->dir );
    if( he > hd )
        return he+1;
    else
        return hd+1;
}


/* ----------------------------------------------------- 
   Verifica se a árvore está completa
*/
int arvCompleta( ArvAVL arv ){
    if( contaNoArv( arv ) == pow(2, alturaArv(arv))-1 )
        return 1;
    return 0;
}

/* ----------------------------------------------------- */
/* Criação de um novo nodo com o valor do Item preenchido com v */
ArvAVL criaNoArv( int v ){
    ArvAVL p;

    p = (ArvAVL)malloc( sizeof(Nodo) );
    if(!p) return NULL;

    p->bal = 0;
    p->item = v;
    p->esq = NULL; 
    p->dir = NULL;

    return p;
}

ArvAVL rotacaoEsq(ArvAVL p){
    ArvAVL dirP;

    dirP = p->dir;
    p->dir = dirP->esq;
    dirP->esq = p; 

    return dirP;
}

ArvAVL rotacaoDir(ArvAVL p){
    ArvAVL esqP;

    esqP = p->esq;
    p->esq = esqP->dir;
    esqP->dir = p; 

    return esqP;
}

void balanceia (ArvAVL *p){
    ArvAVL fp, np;
    if((*p)->bal == 2){
        fp = (*p)->esq;
        if(fp->bal == 1){
            (*p) = rotacaoDir(*p);
            (*p)->bal = 0;
            fp->bal = 0;
        }else if(fp->bal == -1){
            np = fp->dir;
            fp = rotacaoEsq(fp);
            (*p) = rotacaoDir(*p);
            if(np->bal == 1){
                (*p)->bal = -1;
                fp->bal = 0;
            }else if(np->bal == -1){
                (*p)->bal = 0;
                fp->bal = 1;
            }else{
                (*p)->bal = 0;
                fp->bal = 0;
            }
        }
    }else if((*p)->bal == -2){
        fp = (*p)->dir;
        if(fp->bal == -1){
            (*p) = rotacaoEsq(*p);
            (*p)->bal = 0;
            fp->bal = 0;
        }else if(fp->bal == 1){
            np = fp->esq;
            fp = rotacaoDir(fp);
            (*p) = rotacaoEsq(*p);
            if(np->bal == 1){
                (*p)->bal = 0;
                fp->bal = -1;
            }else if(np->bal == -1){
                (*p)->bal = 1;
                fp->bal = 0;
            }else{
                (*p)->bal = 0;
                fp->bal = 0;
            }
        }
    }
}

ArvAVL buscaMaior(ArvAVL p){
    if(p == NULL)
        return NULL;

    if(p->dir == NULL)
        return p;

    return buscaMaior(p->dir);
}

/* ----------------------------------------------------- */ 
/* Insere um novo Item na árvore */
ArvAVL insereArv( int v, ArvAVL arv , int *mudouAltura){
    if( arvVazia( arv )){
        *mudouAltura = 1;
        return criaNoArv( v );
    }
    if(v == arv->item){
        *mudouAltura = 0;
        return arv;
    }

    if(v < arv->item){
        arv->esq = insereArv(v, arv->esq, mudouAltura);
        if(*mudouAltura){
            arv->bal++;
            if(arv->bal == 2)
                balanceia(&arv);
            if(arv->bal == 0)
                *mudouAltura = 0;
        }
    }else{
        arv->dir = insereArv(v, arv->dir, mudouAltura);
        if(*mudouAltura){
            arv->bal--;
            if(arv->bal == -2)
                balanceia(&arv);
            if(arv->bal == 0)
                *mudouAltura = 0;
        }
    }

    return arv;
}

ArvAVL removeR(ArvAVL nodoRem, ArvAVL p, int *mudouH){
    ArvAVL filho;

    /* Remove nodoRem folha ou com filho único. */
    if(p == nodoRem){
        if(p->dir != NULL) filho = p->dir; else filho = p->esq;
        free(p);
        *mudouH = 1;
        return filho;
    }else if(nodoRem->item < p->item){
        p->esq = removeR(nodoRem, p->esq, mudouH);
        if(*mudouH){
            p->bal--;
            if(p->bal == -2)    /* Mesmo balanceando a altura muda. */
                balanceia(&p);
            if(p->bal != 0)     /* A remoção não altera a altura. */
                *mudouH = 0;
        }
    }else{
        p->dir = removeR(nodoRem, p->dir, mudouH);
        if(*mudouH){
            p->bal++;
            if(p->bal == 2)
                balanceia(&p);
            if(p->bal != 0)
                *mudouH = 0;
        }
    }
    return p;
}

void removeArv( int valor , ArvAVL *raiz){
    ArvAVL nodoK, nodoRem;
    int itemRem;
    int mudouH;

    /* Busca do nodo que contém o item. */
    nodoK = buscaArv(valor, *raiz);
    if(nodoK == NULL)
        return;

    /* Busca nodo com dados que vão substituir a chave que será removida. */
    if(nodoK->dir == NULL || nodoK->esq == NULL)
        nodoRem = nodoK;
    else
        nodoRem = buscaMaior(nodoK->esq);
    itemRem = nodoRem->item;

    /* Remove nodoRem da árvore. */
    /* nodoRem é folha ou tem um unico filho. */
    *raiz = removeR(nodoRem, *raiz, &mudouH);
    if(itemRem != valor)
        nodoK->item = itemRem;

    return;
}

ArvAVL buscaArv( int k, ArvAVL arv){
    if(arvVazia(arv))
        return NULL;

    if(k == arv->item)
        return arv;
    
    if(k < arv->item)
        return buscaArv(k, arv->esq);
    else{
        return buscaArv(k, arv->dir);
    }
}

/* ----------------------------------------------------- */
/* Libera espaço alocado para toda a árvore              */
void freeArv( ArvAVL p ){
  if( p != NULL ){
    freeArv( p->esq );
    freeArv( p->dir );
    free( p );
  }
}