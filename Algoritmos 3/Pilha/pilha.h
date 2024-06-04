/*---------------------------------------------------------
Interface: TAD Pilha
-----------------------------------------------------------*/
typedef struct NoPilha *ApNoPilha;
typedef struct NoPilha {
  ItemPilha item;
  ApNoPilha prox;
} NoPilha;

typedef ApNoPilha Pilha;

void criaPilha( Pilha* );
int pilhaVazia( Pilha );
void empilha( ItemPilha, Pilha*);
void desempilha( Pilha*, ItemPilha* );
