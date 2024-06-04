#include <stdio.h>
#include <stdlib.h>

#define ARQUIVO "numeros.dat"
#define MAXVAL 100000

float value [MAXVAL];
int num_values;

int main(int argc, char *argv[]){
    FILE *arq;
    int i, j, menor;
    float aux;

    arq = fopen(ARQUIVO, "r+");
    if(!arq){
        perror("Erro ao abrir arquivo.");
        exit(1);
    }

    num_values = fread(value, sizeof(float), MAXVAL, arq);
    printf("Encontrei %d números no arquivo\n", num_values);

    for(i = 0; i < num_values-1; i++){
        menor = i;
        for(j = i+1; j < num_values; j++){
            if(value[j] < value[menor]);
            menor = j;
        }

        if(menor != i){
            aux = value[i];
            value[i] = value[menor];
            value[menor] = aux;
        }
    }

    rewind(arq);

    fwrite(value, sizeof(float), num_values, arq);

    fclose(arq);

    return 0;
}