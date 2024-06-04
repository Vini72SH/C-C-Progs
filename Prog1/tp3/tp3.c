#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>

/*Cria e insere elementos em um vetor de racionais.*/
void cria_v (struct racional **vet, int tam){
    long int num, den, i;

    for (i = 0; i < tam; i++){
        scanf ("%ld %ld", &num, &den);
        vet[i] = cria_r (num, den);
    }
}

void imprime_v (struct racional **vet, int tam){
    int i;

    for (i = 0; i < tam; i++){
        imprime_r (vet[i]);
        printf (" ");
    }
}

/*Remove os elementos inválidos.*/
void remove_inv (struct racional **vet, int *tam){
    int i;
    struct racional *aux;

    for (i = 0; i < *tam; i++){
        if (!(valido_r (vet[i]))){
            aux = vet[*tam-1];
            vet[*tam-1] = vet [i];
            vet[i] = aux;
            (*tam)--;
            i--;
        }
    }
}

/*Subrotina do MergeSort.*/
void Merge(struct racional **vet, int inicio, int meio, int fim){
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    /*Cria dois vetores temporários de forma dinâmica*/
    struct racional **L = (struct racional **)malloc(n1 * sizeof(struct racional *));
    struct racional **R = (struct racional **)malloc(n2 * sizeof(struct racional *));

    if ((L == NULL) || (R == NULL)){
        perror("Erro na alocação de memória\n");
        exit(1);
    }

    /*Copia metade do vetor principal para cada sub-vetor*/
    for (i = 0; i < n1; i++)
        L[i] = vet[inicio + i];

    for (j = 0; j < n2; j++)
        R[j] = vet[meio + 1 + j];

    /*Ordena o vetor, intercalando os menores elementos.*/
    i = 0;
    j = 0;
    k = inicio;
    while ((i < n1) && (j < n2)){
        if (compara_r(L[i], R[j]) <= 0){
            vet[k] = L[i];
            i++;
        }else{
            vet[k] = R[j];
            j++;
        }
        k++;
    }

    /*Copia os demais elementos do vetor temporário para o principal.*/
    while (i < n1){
        vet[k] = L[i];
        i++;
        k++;
    }

    while (j < n2){
        vet[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

/*Ordena um vetor de racionais.*/
void Merge_Sort (struct racional **vet, int inicio, int fim){
    int meio;

    if (inicio < fim){
        meio = inicio + (fim - inicio) / 2;

        /*Ordena a primeira metade do vetor.*/
        Merge_Sort (vet, inicio, meio);
        /*Ordena a segunda metade do vetor.*/
        Merge_Sort (vet, meio+1, fim);
        /*Combina ambas as partes.*/
        Merge (vet, inicio, meio, fim);
    }
}
/*Retorna a soma de todos os elementos do vetor.*/
struct racional *Soma_Max (struct racional **vet, int tam){
    int i;
    struct racional *r;
    r = cria_r (0, 1);

    for (i = 0; i < tam; i++){
        soma_r (vet[i], r, r);
    }

    simplifica_r (r);
    
    return r;
}

/*Libera a memória alocada para o vetor e para os elementos do vetor.*/
void destroi_v (struct racional **vet, int tam){
    int i;

    for (i = 0; i < tam; i++){
        destroi_r (vet[i]);
    }
    free (vet);
}

int main (){
    int tam, aux_tam;
    struct racional **vet, *soma;
    /* vetor de ponteiros para racionais */

    scanf ("%d", &tam);
    aux_tam = tam;
    vet = (struct racional **)malloc (tam * sizeof (struct racional *));

    cria_v (vet, tam);
    imprime_v (vet, tam);
    printf ("\n");

    remove_inv (vet, &aux_tam);
    imprime_v (vet, aux_tam);
    printf ("\n");

    Merge_Sort(vet, 0, aux_tam-1);
    imprime_v (vet, aux_tam);
    printf ("\n");

    soma = Soma_Max (vet, aux_tam);
    printf ("A soma de todos os elementos eh: ");
    imprime_r (soma);
    printf ("\n");

    destroi_v (vet, tam);
    destroi_r (soma);

    return 0;
}
