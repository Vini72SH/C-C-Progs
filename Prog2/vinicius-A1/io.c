#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

/* Informa os campos e retorna a quantidade de
 * variáveis. */
int le_atributos(FILE* csv){
    int tam;
    char line[LINESIZE + 1];    
    char *token;

    tam = 0;
    fgets(line, LINESIZE, csv);
    token = strtok(line, ",\n");
    while(token != NULL){
        tam++;
        if(strcmp(token, "Nome") == 0){
            printf("%s [S]\n", token);
        }
        if(strcmp(token, "Sexo") == 0){
            printf("%s [S]\n", token);
        }
        if(strcmp(token, "Idade") == 0){
            printf("%s [N]\n", token);
        }
        if(strcmp(token, "Profissao") == 0){
            printf("%s [S]\n", token);
        }
        if(strcmp(token, "Salario") == 0){
            printf("%s [N]\n", token);
        }
        if(strcmp(token, "EC") == 0){
            printf("%s [S]\n", token);
        }
        token = strtok(NULL, ",\n");
    }

    printf("%d variaveis encontradas\n\n", tam);
    rewind(csv);

    return tam;
}

/* Retorna a quantidade de atributos. */
int conta_linhas(FILE *csv){
    int qtd;
    char line[LINESIZE+1];

    qtd = -1;
    while(fgets(line, LINESIZE, csv) != NULL){
        qtd++;
    }

    rewind(csv);

    return qtd;
}
/* Processa os dados do arquivo.
 * retorna um ponteiro para um vetor. */
atributos *processa_dados(FILE *csv, int tam){
    int i;
    char *token;
    char line[LINESIZE + 1];
    atributos *v;

    v = malloc(tam * (sizeof(atributos)));
    if(!v) return NULL;

    i = 0;
    /* Descarta a linha de declaraçao. */
    fgets(line, LINESIZE, csv);
    while(fgets(line, LINESIZE, csv) != NULL){
        token = strtok(line, ",");
        v[i].nome = strdup(token);
        token = strtok(NULL, ",");
        v[i].sexo = strdup(token);
        token = strtok(NULL, ",");
        v[i].idade = strdup(token);
        token = strtok(NULL, ",");
        v[i].profis = strdup(token);
        token = strtok(NULL, ",");
        v[i].salario = strdup(token);
        token = strtok(NULL, ",\n");
        v[i].EC = strdup(token);
        i++;
    }

    rewind(csv);

    return v;
}
    
/* Imprime os dados processados. */
void imprime_dados(atributos *v, int tam){
    int i;

    printf("  Nome    Sexo  Idade  Profissao                   Salario       EC\n");
    if(tam < 10){
        for(i = 0; i < tam; i++){
            printf("%d ", i);
            printf("%-10s", v[i].nome);
            printf("%-5s", v[i].sexo);
            printf("%-5s", v[i].idade);
            printf("%-30s", v[i].profis);
            printf("%-10s", v[i].salario);
            printf("%-10s\n", v[i].EC);
        }
    }else{
        for(i = 0; i < 5; i++){
            printf("%6d ", i);
            printf("%-10s", v[i].nome);
            printf("%-5s", v[i].sexo);
            printf("%-5s", v[i].idade);
            printf("%-30s", v[i].profis);
            printf("%-10s", v[i].salario);
            printf("%-10s\n", v[i].EC);
        }
        printf("...          ...  ...    ...                      ...       ...         ...\n");
        for(i = 5; i > 0; i--){
            printf("%6d ", tam-i);
            printf("%-10s", v[tam-i].nome);
            printf("%-5s", v[tam-i].sexo);
            printf("%-5s", v[tam-i].idade);
            printf("%-30s", v[tam-i].profis);
            printf("%-10s", v[tam-i].salario);
            printf("%-10s\n", v[tam-i].EC);
        }
    }
}   

/* Libera toda a memória alocada.*/
void libera_mem(atributos *v, int tam){
    int i;

    for(i = 0; i < tam; i++){
        free(v[i].nome);
        free(v[i].sexo);
        free(v[i].idade);
        free(v[i].profis);
        free(v[i].salario);
        free(v[i].EC);
    }

    free(v);
}