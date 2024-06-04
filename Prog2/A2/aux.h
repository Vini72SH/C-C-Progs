#ifndef __aux__
#define __aux__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1024

/* Retorna a quantidade de dígitos de num. */
int conta_digitos(int num);

/* Separa a linha e retorna a palavra
 * antes da primeira vírgula. */
char* separa(const char *string);

/* Imprime o char " ", num vezes. */
void cria_espacos(int num);

/* Cria um vetor contendo as palavras de uma string.
 * Tam é a quantidade de palavras contidas na string. 
 * No fim, o vetor contém uma palavra em cada indíce. */
void cria_vetor(char **v, int tam, char *linha);

/* Libera o vetor de strings, dando free nas strings. */
void libera_strings(char **v, int tam);

/* Preenche um vetor com tamanho tam
 * com o caracter c. */
void preenche_vetor(char v[], int tam, char c);

#endif