#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    struct No *proximo;
}No;

typedef struct{
    No *inicio;
    int tam;
}Lista;

void inserirInicio(Lista *lista, int valor){
    No *novo = (No*)malloc(sizeof(No));

    novo->valor = valor;
    /*Aponta para o antigo primeiro elemento.*/
    novo->proximo = lista->inicio;
    /*Se torna o primeiro elemento da lista.*/
    lista->inicio = novo;
    lista->tam++;
}

void inserirFim (Lista *lista, int valor){
    No *no, *novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->proximo = NULL;

    /*Se a lista estiver vazia, ele simplesmente é posicionado no começo.*/
    if(lista->inicio == NULL){
        lista->inicio = novo;
    /*Se não, percorre até o último elemento e aponta para o novo no.*/
    }else{
        no = lista->inicio;
        while (no->proximo != NULL){
            no = no->proximo;
        }
        no->proximo = novo;
    }
    lista->tam++;
}

void remover (Lista *lista, int valor){
    No *inicio = lista->inicio;
    No *noARemover = NULL;

    /*Remove o elemento caso ele seja o primeiro da lista*/
    if(lista->inicio != NULL && lista->inicio->valor == valor){
        noARemover = lista->inicio;
        lista->inicio = noARemover->proximo;
    }else{
        /*Descarta o no atual e avalia o valor do próximo, se ele é o último
         * ou se é o no correto.*/
        while(inicio != NULL && inicio->proximo != NULL && inicio->proximo->valor != valor){
        inicio = inicio->proximo;
        }

        if (inicio != NULL && inicio->proximo != NULL){
            noARemover = inicio->proximo;
            inicio->proximo = noARemover->proximo;
        }
    }

    if (noARemover){
        free(noARemover);
        lista->tam--;
    }
}

void imprimir (Lista *lista){
    No *inicio = lista->inicio;
    printf("Tamanho da lista: %d\n", lista->tam);
    while (inicio != NULL){
        printf ("%d ", inicio->valor);
        inicio = inicio->proximo;
    }
    printf ("\n\n");
}

int main(){
    int opcao, valor;
    Lista lista;

    lista.inicio = NULL;
    lista.tam = 0;

    do{
        printf("1 - Inserir no Inicio\n2 - Imprimir\n3 - Inserir no Fim\n4 - Remover Elemento\n5 - Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
        case 1:
            printf ("Digite um valor para inserir: ");
            scanf ("%d", &valor);
            inserirInicio(&lista, valor);
            break;
        case 2:
            imprimir(&lista);
            break;
        case 3:
            printf("Digite um valor para inserir: ");
            scanf ("%d", &valor);
            inserirFim(&lista, valor);
            break;
        case 4:
            printf("Digite um valor para remover: ");
            scanf("%d", &valor);
            remover(&lista, valor);
            break;
        case 5:
            printf ("Finalizando...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    }while (opcao != 5);

    return 0;
}

