#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "racionais.h"

/*Gera um vetor com racionais aleatórios*/
void gera_vetor (struct racional v[], int tam){
    int i;

    /*O numerador e denominador estão entre
    -tam e tam*/
    for (i = 0; i < tam; i++){
        v[i] = sorteia_r (tam);
    }
}

/*Imprime um vetor*/
void imprime_v (struct racional v[], int tam){
    int i;

    for (i = 0; i < tam; i++){
        imprime_r (v[i]);
        printf (" ");
    }
    printf ("\n");
}

void remove_inv (struct racional v[], int *tam){
    int i, j;
    for (i = 0; i < *tam; i++){
        if (!(valido_r(v[i])) || (v[i].den == 0)){
            for (j = i; j < *tam - 1; j++){
                v[j] = v[j + 1];
            }
            (*tam)--;
            i--;
        }
    }
}

void ordena_v (struct racional v[], int tam){
    int i, j;
    struct racional aux;

    for (i = 0; i < tam - 1; i++){
        for (j = i + 1; j < tam; j++){
            if ((compara_r (v[i], v[j])) == 1){
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
}

struct racional somaMAX (struct racional v[], int tam){
    int i;
    struct racional soma;
    soma = cria_r (0, 1);
    for (i = 0; i < tam; i++){
        soma_r (soma, v[i], &soma);
    }

    return soma;
}

int main (){
    /*Inicialização da semente randomica*/
    srand (time(0));

    int n;

    /*Leitura do tamanho do vetor*/
    scanf ("%d", &n);

    struct racional v[n], soma_max;

    /*Constrói um vetor com racionais
    aleatórios*/
    gera_vetor(v, n);
    imprime_v (v, n);

    /*Remove os racionais inválidos do vetor*/
    remove_inv (v, &n);
    imprime_v (v, n);

    /*Ordena o novo vetor*/
    ordena_v (v, n);
    imprime_v (v, n);

    soma_max = somaMAX (v, n);
    printf ("a soma de todos os elementos eh: ");
    imprime_r (soma_max);

    printf("\n");

    return 0;
}
