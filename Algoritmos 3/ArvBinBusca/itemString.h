/* ----------------------------------------------------------
Definições e macros para tratamento do TipoItem char*
*/
#include <string.h>

#define TAM 50

typedef char Item[TAM];

#define FIM "fim"
#define ERRO "erro"

#define eq(A, B)  (strcmp(A, B) == 0)
#define gt(A, B)  (strcmp(A, B) > 0)
#define lt(A, B)  (strcmp(A, B) < 0)
#define geq(A, B) (strcmp(A, B) >= 0)
#define leq(A, B) (strcmp(A, B) <= 0)
#define cp(A, B)  (strcpy(A, B))
#define read(A)   (scanf("%s", A))
#define write(A)  (printf("%s", A))

