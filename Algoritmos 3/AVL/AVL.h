#ifndef __AVL__
#define __AVL__

/*===================================*/
/*       Interface Árvore AVL        */
/*===================================*/

typedef struct Nodo *ApNodo;
typedef struct Nodo {
    int bal;
    int item;
    ApNodo esq;
    ApNodo dir;
}Nodo;

typedef ApNodo ArvAVL;

void criaArv( ArvAVL* );
int arvVazia( ArvAVL );
void balanceia(ArvAVL*);
ArvAVL insereArv( int, ArvAVL, int*);
void removeArv( int, ArvAVL* );
ArvAVL buscaArv( int, ArvAVL );
void escreveArv( ArvAVL );
void ArvEmOrdem( ArvAVL );
void ArvPreOrdem( ArvAVL );
void ArvPosOrdem( ArvAVL );
int alturaArv( ArvAVL );
int contaNoArv( ArvAVL );
int arvCompleta( ArvAVL ); 
void freeArv( ArvAVL );

#endif