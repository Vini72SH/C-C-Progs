#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]){
    char csv_line[257];

    /* Fazendo demarcação */
    csv_line[255] = 0;

    /* Leitura da string */
    printf("Digite a linha CSV (max. 255 carac.): ");
    scanf("%256[^\n]", csv_line);
    getchar();

    /* Verificando leitura -- forçando tamanho máx. de 255 caracteres*/
    if (csv_line[255]){
        printf("A linha excedeu o tamamnho máximo [255 caracteres]!\n");
        return -1;
    }

    /* Processando as colunas */
    int c;
    char *keeper, *search;
    for (keeper = csv_line, search = strchr(csv_line, ','), c = 1; //
        search; //
        keeper = search+1, search = strchr(keeper, ','), c++){
        search[0] = 0;
        printf("Coluna %d: %s\n", c, keeper);
    }
    printf("Coluna %d: %s\n", c, keeper);

    return 0;
}

