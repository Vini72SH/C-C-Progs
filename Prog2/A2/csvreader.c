#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "io.h"

int main(int argc, char** argv){
    int op;
    arq_csv *arquivo;
    char *entrada, file_name[100], var[100];

    if(argc != 2){
        printf("Inicialização incorreta!\n");
        printf("Execute: %s <arquivo.csv>\n", argv[0]);
        return 0;
    }

    entrada = strdup(argv[1]);
    arquivo = abre(entrada);

    if(entrada == NULL){
        perror("Não foi possível alocar memória.\n");
        return 0;
    }

    printf("--- LEITOR E PROCESSADOR CSV ---\n");
    do{
        printf("1) Sumário do arquivo\n");
        printf("2) Mostrar\n");
        printf("3) Filtros\n");
        printf("4) Descrição dos Dados\n");
        printf("5) Ordenação\n");
        printf("6) Seleção\n");
        printf("7) Dados Faltantes\n");
        printf("8) Salvar Dados\n");
        printf("9) Fim\n");
        printf("Selecione a opção: ");
        scanf("%d", &op);
        getchar();
        printf("\n");

        switch(op){
            case 1:
                sumario(arquivo);
                break;
            case 2:
                exibe(arquivo);
                break;
            case 3:
                unidade_de_filtro(arquivo);
                break;
            case 4:
                printf("Entre com a variavel: ");
                scanf("%s", var);
                descricao(var, arquivo);
                break;
            case 5:
                printf("Entre com a variavel: ");
                scanf("%s", var);
                ordenacao(var, arquivo);
                break;
            case 6:
                printf("Entre com as variaveis que deseja selecionar (separadas por espaço): ");
                scanf("%[^\n]", var);
                selecao(var, arquivo);
                break;
            case 7:
                dados_faltantes(arquivo);
                break;
            case 8:
                printf("Entre com o nome do arquivo: ");
                scanf("%s", file_name);
                salvar_dados(file_name, arquivo);
                break;
            case 9:
                break;
            default:
                printf("Digite uma entrada válida!\n\n");
        }
    }while(op != 9);

    free(entrada);
    arquivo = fecha(arquivo);

    return 0;
}