#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1024

typedef struct coluna{
    char **v;
}coluna;

char *separa(char *linha){
    char *pos_virgula;

    if(!linha) return NULL;

    pos_virgula = strchr(linha, ',');
    if(!pos_virgula){
        if(strlen(linha))
            return linha;
        return NULL;
    }

    *pos_virgula = '\0';

    return linha;
}

void lin_col(int *lin, int *col, FILE *arq){
    int i, j;
    char *token;
    char line[LINESIZE + 1];

    i = 0;
    j = 0;

    /* Coleta a quantidade de colunas. */
    fgets(line, LINESIZE, arq);
    token = strtok(line, ",\n");
    while(token != NULL){
        j++;
        token = strtok(NULL, ",\n");
    }

    /* Coleta a quantidade de linhas. */
    while(fgets(line, LINESIZE, arq) != NULL){
        i++;
    }

    (*lin) = i;
    (*col) = j;

    rewind(arq);
}

coluna *criaMatriz(int lin, int col){
    int i;
    coluna *v;

    /* Alocação de Memória. */
    v = malloc(lin * sizeof(coluna));
    if(!v) return NULL;

    /* Alocação de Memória das colunas. */
    for(i = 0; i < lin; i++){
        v[i].v = malloc(col * sizeof(char *));
        if(!(v[i].v)) {
            perror("Erro na alocação de memória.");
            exit(1);
        }
    }

    return v;
}

void insere_dados(coluna *m, FILE *arq){
    int i, j;
    char *token;
    char *ptr;
    char line[LINESIZE+1];

    /* Descarta a linha de declaracao de campos.*/
    fgets(line, LINESIZE, arq);

    /* Insere as strings na matriz */
    i = 0;
    while(fgets(line, LINESIZE, arq) != NULL){
        j = 0;
        token = separa(line);
        if(strlen(token) > 1){
            m[i].v[j] = strdup(token);
        }else{
            m[i].v[j] = strdup("NaN");
        }
        while((token = separa(token + (strlen(token) + 1)))){
            j++;
            if(strlen(token) > 1){
                m[i].v[j] = strdup(token);
            }else{
                m[i].v[j] = strdup("NaN");
            }   
        }
        i++;
    }   

    rewind(arq);
}

void imprime_matriz(coluna *m, int lin, int col){
    int i, j;

    if(!m) return;

    for(i = 0; i < lin; i++){
        for(j = 0; j < col; j++){
            printf("%10s", m[i].v[j]);
        }
        printf("\n");
    }
    printf("\n");
}

void deleta_Matriz(coluna *m, int lin, int col){
    int i, j;

    if(!m) return;

    /* Percorre todos os campos da matriz liberando memória. */
    for(i = 0; i < lin; i++){
        for(j = 0; j < col; j++){
            free(m[i].v[j]);
        }
        free(m[i].v);
    }
    free(m);
}

int main(){
    FILE *arq;
    coluna *m, aux;
    int lin, col;

    arq = fopen("texto.txt", "r");
    if(!arq){
        perror("Erro ao abrir arquivo.\n");
        exit(1);
    }

    lin_col(&lin, &col, arq);
    
    m = criaMatriz(lin, col);
    printf("Matriz criada com sucesso!\n\n");

    insere_dados(m, arq);
    imprime_matriz(m, lin, col);

    deleta_Matriz(m, lin, col);

    fclose(arq);

    return 0;
}