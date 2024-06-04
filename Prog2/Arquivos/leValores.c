#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *arq;
    int i, ret;
    float value;

    arq = fopen("numeros.txt", "r");
    if(!arq){
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    /* Leitura de 10 valores do arquivo. */
    i = 0;
    while(i < 15){
        ret = fscanf(arq, "%f", &value);

        /* Fim do arquivo ou erro? */
        if(ret == EOF){
            break;
        }

        /* Houve leitura? */
        if(ret > 0){
            printf("%d: %f\n", i, value);
            i++;
        }else{
            fgetc (arq);
        }
    }

    fclose(arq);

    return 0;
}