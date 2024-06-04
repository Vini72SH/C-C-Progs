#ifndef __filtros__
#define __filtros__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*OpFiltro)(char *, char *);

/* Recebe a string s1 e o valor
 * Retorna 1 se s1 for igual ao valor. */
int filtraIgual(char *s1, char *valor);

/* Recebe a string s1 e o valor
 * Retorna 1 se s1 for maior que valor. */
int filtraMaior(char *s1, char *valor);

/* Recebe a string s1 e o valor
 * Retorna 1 se s1 for maior ou igual que valor. */
int filtraMaiorIgual(char *s1, char *valor);

/* Recebe a string s1 e o valor
 * Retorna 1 se s1 for menor ou igual que valor. */
int filtraMenorIgual(char *s1, char *valor);

/* Recebe a string s1 e o valor
 * Retorna 1 se s1 for menor que valor. */
int filtraMenor(char *s1, char *valor);

/* Recebe a string s1 e o valor
 * Retorna 1 se s1 for diferente que valor. */
int filtraDiferente(char *s1, char *valor);

/* Recebe uma string com o comparador como parâmetro
 * Retorna: Ponteiro para o filtro correspondente. */
OpFiltro retornaFiltro(char *fil);

#endif