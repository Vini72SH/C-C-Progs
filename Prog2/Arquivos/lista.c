#include <stdio.h>
#include <stdlib.h>

#define ARQUIVO "numeros.dat"

int main(int argc, char *argv[]){
    FILE *arq;
    float value;

    arq = fopen(ARQUIVO, "r");
    if(!arq){
        perror("Erro ao abrir arquivo.");
        exit(1);
    }

    fread(&value, sizeof(float), 1, arq);
    while(!(feof(arq))){
        printf("%f\n", value);
        fread(&value, sizeof(float), 1, arq);
    }
    fclose(arq);

    return 0;
}