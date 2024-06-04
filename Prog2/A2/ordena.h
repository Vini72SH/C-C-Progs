#ifndef __ordena__
#define __ordena__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Recebe um vetor e o inverte. */
void inverte_vetor(int *aux, int tam);

/* Compara duas strings e retorna
 * 1 se s1 <= s2. */
int comparaS(char *s1, char *s2);

/* Merge_Sort tradicional, ordena o vetor de indices ind
 * apartir das strings no vetor char **v */
void Merge(char **v, int ini, int meio, int fim, int *ind);

/* Chamada principal do Merge_Sort */
void Merge_Sort(char **v, int ini, int fim, int *ind);

#endif