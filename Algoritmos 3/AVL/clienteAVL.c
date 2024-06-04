#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

int main(){
    ArvAVL AVL;
    int op, d, mh;

    criaArv(&AVL);
    printf("=== Árvore Digital AVL ===\n");

    do{
        printf("=========================\n");
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Buscar\n");
        printf("4 - Imprimir em ordem\n");
        printf("5 - Imprimir em pré-ordem\n");
        printf("6 - Imprimir em pós-ordem\n");
        printf("7 - Imprimir árvore completa\n");
        printf("8 - Encerrar programa\n");
        printf("Selecione a opção: ");
        scanf("%d", &op);
        printf("\n");

        switch (op){
        case 1:
            printf("Digite os valores (Termine com 0): ");
            scanf("%d", &d);
            while(d != 0){
                AVL = insereArv(d, AVL, &mh);
                scanf("%d", &d);
            }
            break;
        case 2:
            printf("Digite o valor a remover: ");
            scanf("%d", &d);
            removeArv(d, &AVL);
            break;
        case 3:
            printf("Digite a chave para buscar: ");
            scanf("%d", &d);
            if(buscaArv(d, AVL))
                printf("A chave está na árvore.\n");
            else
                printf("Chave não encontrada na árvore\n");
            break;
        case 4:
            ArvEmOrdem(AVL);
            printf("\n");
            break;
        case 5:
            ArvPreOrdem(AVL);
            printf("\n");
            break;
        case 6:
            ArvPosOrdem(AVL);
            printf("\n");
            break;
        case 7:
            escreveArv(AVL);
            printf("\n");
            break;
        case 8:
            break;                        
        default:
            printf("Selecione uma opção válida.\n");
            break;
        }

    }while(op != 8);

    freeArv(AVL);

    return 0;
}