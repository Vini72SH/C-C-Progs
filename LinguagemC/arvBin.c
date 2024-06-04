#include <stdio.h>
#include <stdlib.h>

#define OK    1
#define ERRO -1

typedef long TipoItem;
typedef struct Nodo *ApNodo;
typedef struct Nodo {
  TipoItem item;
  ApNodo esq, dir;
} Nodo;

/* ----------------------------------------------------- */
/* Função de inicialização de uma árvore vazia */
void inicializa(ApNodo *arv){
  *arv = NULL;
}

/* ----------------------------------------------------- */
/* Criação de um novo nodo com o valor do Item preenchido com v */
ApNodo criaNo( TipoItem v ){
  ApNodo p;

  p = (ApNodo)malloc( sizeof(Nodo) );
  p->item = v; p->esq = NULL; p->dir = NULL;
  return p;
}

/* ----------------------------------------------------- */
/* Inserção de um novo nodo na árvore como um nodo folha */
int insere(TipoItem v, ApNodo *p){
  if (*p == NULL)
     *p = criaNo( v ); 
  else if (v < (*p)->item)
    insere(v, &(*p)->esq); 
  else if (v > (*p)->item)
    insere(v, &(*p)->dir);
  else
    return ERRO;  /* a chave ja' existe */
  return OK;
} 

/* Insercao de valores na árvore até digitar um valor <= 0 */
void insereItens( ApNodo *arv ){ 
  TipoItem x;
  int status;
  
  printf("Insercao:\n");
  scanf("%ld", &x);
  while (x > 0)
  {
    status = insere ( x , arv ) ;
    if( status == ERRO)
      printf("ERRO: %ld ja' existe\n", x);
    scanf("%ld", &x);
  }
}

/* ----------------------------------------------------- */
/* Impressão da árvore */
void escreveNodo( char *v, int h ){
  int i;

  for( i=0; i<h; i++ )
    printf( "   " );
  printf( "%s\n", v );
}

void escreveArv( ApNodo p, int h ){
  char s[5];

  if( p == NULL ){
    escreveNodo( "*", h );
    return;
  }
  escreveArv( p->dir, h+1 );
  sprintf( s, "%ld", p->item );
  escreveNodo( s, h );
  escreveArv( p->esq, h+1 );
}

/* ----------------------------------------------------- */
/* Retorna a quantidade de nodos internos na arvore      */
int contaNodo( ApNodo p ){
    if( p == NULL )
        return 0;
    return 1 + contaNodo( p-> esq ) + contaNodo( p->dir );
}

/* ----------------------------------------------------- */
/* Retorna a altura da arvore com raiz em p */
int altura( ApNodo p ){
    int he, hd;

    if( p == NULL )
        return 0;
    he= altura( p-> esq );
    hd= altura( p->dir );
    if( he > hd )
        return he+1;
    else
        return hd+1;
}

/* ----------------------------------------------------- */
/* Retorna o comprimento do caminho da arvore com raiz em p
   Chamada: comprimentoCaminho( p, 0 )                   */
int comprimentoCaminho( ApNodo p, int h ){
    if( p == NULL )
        return h;
    return h + comprimentoCaminho( p-> esq, h+1 ) 
            + comprimentoCaminho( p->dir, h+1 );
}

/* ----------------------------------------------------- */
/* Programa: cria uma árvore binária e calcula algumas propriedades:
   1) quantidade de nodos internos
   2) altura da árvore
   3) comprimento do caminho da arvore

Os valores são inseridos na árvore até que seja digitado um valor <= 0.
*/
int main(){
  ApNodo arv;
  
  inicializa( &arv );
  insereItens( &arv );
  escreveArv( arv, 0 );

  printf( "Nodos internos = %d\n", contaNodo( arv ));
  printf( "Altura = %d\n", altura( arv ));
  printf( "Comprimento do caminho da arvore = %d\n", comprimentoCaminho( arv, 0 ) );
  return 0;

  
}

