#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *arq;
    unsigned char c;

    /* Escrita do arquivo. */
    arq = fopen("ascii.txt", "w+");
    if(!arq){
        perror("Erro ao abrir/criar arquivo.");
        exit(1);
    }

    /* Escreve os caracteres */
    fputs("caracteres ASCCI:", arq);
    for(c = 32; c < 128; c++){
        fputc(c, arq);
        fputc(' ', arq);
    }
    fputc('\n', arq);

    /* Fechar o arquivo. */
    fclose(arq);

    return 0;
}
