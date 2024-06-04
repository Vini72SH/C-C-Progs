/* ----------------------------------------------------------
Definições e macros para tratamento do TipoItem Apontador
*/

typedef void *Item;

#define FIM 0
#define ERRO -1

#define eq(A, B)  (A == B)
#define gt(A, B)  (A > B)
#define lt(A, B)  (A < B)
#define geq(A, B) (A >= B)
#define leq(A, B) (A <= B)
#define cp(A, B)  (A= B)
#define read(A)   (scanf("%p", A))
#define write(A)  (printf("%p", A))
