#include <stdio.h>
#include <stdlib.h>

#define LINESIZE 1024

int main(){
    FILE *arq;
    int i;
    char line[LINESIZE + 1];

    /* Abre o arquivo em leitura. */
    arq = fopen("tabuada.txt", "r");
    if(!arq){
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    /*Lê TODAS as linhas do arquivo. */
    i = 1;
    fgets(line, LINESIZE, arq);
    while(!(feof(arq))){
        printf("%4d: %s", i, line);
        fgets(line, LINESIZE, arq);
        i++;
    }

    fclose(arq);

    return 0;
}