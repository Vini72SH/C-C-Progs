#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARQUIVO "numeros.dat"
#define NUMVAL 10

int main(int argc, char *argv[]){
    FILE *arq;
    int i, ret;
    float value[NUMVAL];

    arq = fopen(ARQUIVO, "a");
    if(!arq){
        perror("Erro ao abrir arquivo.");
        exit(1);
    }

    srand(clock());

    for(i = 0; i < NUMVAL; i++){
        value[i] = random() / 10000.0;
    }

    ret = fwrite(value, sizeof(float), NUMVAL, arq);
    if(ret){
        printf("Gravou %d valores com sucesso!\n", ret);
    }else{
        printf("Erro ao gravar...\n");
    }

    fclose(arq);

    return 0;
}   