#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gera_vetor(int v[], int tam){
    int i;

    for(i = 0; i < tam; i++){
        v[i] = rand() % (tam+1);
    }
}

void imprime_v(int v[], int tam){
    int i;

    for(i = 0; i < tam; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

int soma_vetorial(int v[], int a, int b){
    int m1, m2;
    
    if (a > b){
        return 0;
    }

    if(a == b){
        return v[a];
    }

    m1 = a + (b - a)/3;
    m2 = a + 2*(b - a)/3;

    return soma_vetorial(v, a, m1) + soma_vetorial(v, m1+1, m2) + soma_vetorial(v, m2+1, b);

}

int main (){
    srand(0);
    int n, soma_max;

    scanf("%d", &n);
    int v[n];

    gera_vetor(v, n);
    imprime_v(v, n);

    soma_max = soma_vetorial (v, 0, n-1);

    printf("Soma total dos elementos do vetor: %d\n", soma_max);

    return 0;
}