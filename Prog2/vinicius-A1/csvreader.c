#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

int main(int argc, char **argv){
    int op, tam;
    FILE *arq;
    char *entrada;
    atributos *infos;

    entrada = strdup(argv[1]);
    arq = fopen(entrada, "r");
    if(!arq){
        perror("Erro ao abrir arquivo.");
        exit(1);
    }

    tam = conta_linhas(arq);
    infos = processa_dados(arq, tam);

    do {
        printf("1) Sumario do arquivo.\n");
        printf("2) Mostrar.\n");
        printf("3) Fim.\n");
        printf("Digite sua opcao: ");
        scanf("%d", &op);
        printf("\n");
        switch(op){
            case 1:
                le_atributos(arq);
                printf("Pressione Enter para continuar.\n");
                break;
            case 2:
                imprime_dados(infos, tam);
                printf("Pressione Enter para continuar.\n");
                break;
            case 3:
                break;
            default:
                printf("Por favor, entre com uma opçao valida.\n");
        }
    } while(op != 3);

    libera_mem(infos, tam);
    free(entrada);
    fclose(arq);
    return 0;
}