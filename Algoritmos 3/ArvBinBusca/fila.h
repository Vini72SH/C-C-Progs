/*---------------------------------------------------------
Interface: TAD Pilha
-----------------------------------------------------------*/
typedef struct NoFila *ApNoFila;
typedef struct NoFila {
  ItemFila item;
  ApNoFila prox;
} NoFila;

typedef struct Fila{
  ApNoFila prim, ult;
} Fila;  

void criaFila( Fila* );
int filaVazia( Fila );
void insereFila( ItemFila, Fila*);
void removeFila( Fila*, ItemFila* );
