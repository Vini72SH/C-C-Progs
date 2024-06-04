#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Busca(int x, int v[], int a, int b, int *comp){
    int m, r;

    if(a > b){
        return -1;
    }
    m = (a + b)/2;

    (*comp)++;
    if(x == v[m]){
        return m;
    }

    r = Busca(x, v, a, m-1, comp);
    if(r != -1){
        return r;
    }
    return Busca(x, v, m+1, b, comp);
}

void gera_vetor(int v[], int tam){
    int i;

    for(i = 0; i < tam; i++){
        v[i] = rand() % 101;
    }
}

void imprime(int v[], int tam){
    int i;
    for(i = 0; i < tam; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main(){
    srand(time(0));
    int n, x, pos;
    int comp = 0;

    printf("Tamanho do vetor: ");
    scanf("%d", &n);
    int v[n];

    gera_vetor(v, n);
    imprime(v, n);

    printf("Elemento para buscar: ");
    scanf("%d", &x);
    pos = Busca(x, v, 0, n-1, &comp);

    if(pos != -1){
        printf("Posição do elemento: %d\n", pos);
    }else{
        printf("Não encontrado\n");
    }

    printf("N° de Comparações: %d\n", comp);

    return 0;
}