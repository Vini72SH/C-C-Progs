#ifndef __io__
#define __io__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lista.h"
#include "ordena.h"
#include "aux.h"
#include "filtros.h"

#define LINESIZE 1024

typedef struct double_media{
    int qtd; /* Quantidade de dados. */
    double soma; /* Soma de todos os dados. */
}double_media;


typedef struct arq_csv{
    FILE *arq; /* Ponteiro para o arquivo. */
    unsigned long int linhas_totais; /* Linhas máximas do arquivo. */
    unsigned long int linhas; /* Qtd de linhas do vetor auxiliar. */
    unsigned long int colunas; /* Qtd de colunas dos campos. */
    char **fields; /* Vetor de strings contém campos do arquivo. */
    char **files; /* Vetor de strings armazena todas as linhas do arquivo. */
    char *tipos; /* Vetor de char contém os tipos de cada campo. */
    int *aux_files; /* Vetor de int contendo os índices de cada linha. */
}arq_csv;

/* Abre o arquivo e preenche as informações
 * da estrutura de arquivos CSV. */
arq_csv *abre(char *file_name);

/* Percorre o arquivo CSV coletando e
 * armazenando seus dados. */
arq_csv *verifica(arq_csv *arquivo);

/* Imprime o sumário do arquivo.
 * Campos e seus respectivos tipos. */
void sumario(arq_csv *arquivo);

/* Recebe uma string e o tamanho máximo de cada campo
 * concatena as palavras com espaços em branco e
 * retorna um ponteiro para uma nova string formatada. */
char *formata(char *string, int *sizes);

/* Chama a função imprime com os paramêtros corretos para a main. */
void exibe(arq_csv *arquivo);

/* Imprime os campos do arquivo, suas primeiras cinco linhas e 
 * últimas cinco linhas de forma formatada, baseado na maior palavra
 * de cada campo. */
void imprime(char **fields, char **files, int *ind, int lin, int col);

/* Filtra todos os dados após definir as condições.
 * Permite que seja criado um novo arquivo e também descartar os dados antigos. 
 * Recebe o arquivo, o índine da coluna a ordenar e o ponteiro para função filtro. */
void filtro(arq_csv *arquivo, int indice, OpFiltro filtrador, char *valor);

/* Recebe os parâmetros para o filtro e redireciona as funções. */
void unidade_de_filtro(arq_csv *arquivo);

/* Imprime as informações da coluna com vetor de indices.
 * O campo type indica se a coluna é de strings ou números. */
void vetor_info(char **v, int tam, int *ind, char type);

/* Faz a coleta de dados da coluna selecionada e imprime
 * suas estatísticas gerais. */
void descricao(char *col_selec, arq_csv *arq);

/* Ordena o arquivo com base na coluna selecionada de forma crescente
 * ou decrescente e possibilita salvar o arquivo e substituir os dados originais. */
void ordenacao(char *col_selec, arq_csv *arq);

/* Seleciona as colunas inseridas pelo usuário
 * imprime os dados e salva em arquivo caso o usuário desejar. */
void selecao(char *variaveis, arq_csv *arq);

/* Função para tratar eventos relacionados aos dados faltantes. */
void dados_faltantes(arq_csv *arq);

/* Procura todos os dados faltantes de um arquivo e calcula a média das 
 * colunas númericas, além de inserir no vetor de inválidas os indíces.
 * Retorna o tamanho do vetor de inválidos. */
int procura_dados(arq_csv *arq, int *invalidas, double_media *medias);

/* Percorre as linhas inválidas e cria novas linhas inserindo a média nas colunas númericas. */
void substituir_media(char **files, char *tipos, int *invalidas, double_media *medias, int lin, int col);

/* Percorre as linhas inválidas e substitui os campos vazios pelo próximo campo válido. */
void substituir_valor(char **files, int *invalidas, int lin, int col);

/* Permite que o usuário selecione as variáveis que possuem dados faltantes 
 * e remove as linhas do arquivo, retorna o novo tamanho do vetor de índices.
 * Retorna o novo tamanho do vetor de indíces. */
int remove_invalidos(int *indices, char **files, char **fields, int *invalidos, int tamInd, int tamInv, int col);

/* Passa os parâmetros corretos para a função 
 * de gerar arquivo. */
void salvar_dados(char *file_name, arq_csv *arquivo);

/* Passa os paramêtros para salvar o arquivo.
 * Retorna 1 se o usuário optar por descartar os dados antigos. */
int salvar_arq(arq_csv *arq, int *aux, int tam);

/* Gera um novo arquivo com o nome inserido pelo usuário.
 * Recebe o nome do arquivo, o vetor com os campos do arquivo
 * o vetor com as linhas do arquivo, o vetor auxiliar de índices
 * e a quantidade de linhas e colunas do novo arquivo. */
int gera_arquivo(char *file_name, char **fields, char **files, int *ind, int lin, int col);

/* Fecha o arquivo e libera toda a memória
 * alocada pelo programa. */
arq_csv *fecha(arq_csv *arquivo);

#endif