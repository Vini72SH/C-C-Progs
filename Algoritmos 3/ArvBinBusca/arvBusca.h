/*---------------------------------------------------------
Interface: TAD Arvore
-----------------------------------------------------------*/
typedef struct Nodo *ApNodo;
typedef struct Nodo {
  ItemArv item;
  ApNodo esq, dir;
  int n;
} Nodo;

typedef ApNodo ArvBusca;

void criaArv( ArvBusca* );
int arvVazia( ArvBusca );
ArvBusca insereArv( ItemArv, ArvBusca );
ArvBusca insereNaRaiz (ItemArv, ArvBusca);
void escreveArv( ArvBusca );
int alturaArv( ArvBusca );
int contaNoArv( ArvBusca );
int arvCompleta( ArvBusca ); 
void freeArv( ArvBusca );
ArvBusca buscaArv( ItemArv, ArvBusca );
ArvBusca buscaElementoK( int, ArvBusca );
void visitaOrdenado( ArvBusca, void (*funcao)(Item) );
