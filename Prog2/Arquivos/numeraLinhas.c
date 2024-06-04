#include <stdio.h>
#include <stdlib.h>

#define LINESIZE 1024

int main(){
    FILE *arq;
    int i;
    char line[LINESIZE+1];

    /* Abre o arquivo em leitura. */
    arq = fopen("tabuada.txt", "r");
    if(!arq){
        perror("Erro ao abrir arquivo.");
        exit(1);
    }

    /* Lê as primeiras i linhas do arquivo. */
    for(i = 0; i < 14; i++){
        fgets(line, LINESIZE, arq);
        printf("%4d: %s", i, line);
    }

    fclose(arq);

    return 0;
}