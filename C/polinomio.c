#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gera_vetor(int v[], int tam){
    int i; 

    for (i = 0; i < tam; i++){
        v[i] = rand() % (tam+1);
    }
}

void imprime_v(int v[], int tam){
    int i;

    printf("F(x) = ");
    for(i = tam-1; i >= 0; i--){
        printf("%dx^%d + ", v[i], i);
    }
    printf("0");
    printf("\n");
}

int expo(int x, int n){
    if(n == 0){
        return 1;
    }

    return x * expo(x, n-1);
}

int expo2(int x, int n){
    if (n == 0){
        return 1;
    }  

    if(n == 1){
        return x;
    }

    return expo2(x, n % 2) * (expo2(x, n / 2) * expo2(x, n / 2));
}

int Pol(int v[], int a, int b, int x){
    int n;

    if(a == b){
        return v[a];
    }
    n = b - a;
    return v[b]*expo(x, n) + Pol(v, a, b-1, x);
}

int Poli2(int v[], int a, int b, int x){
    int m, left, right;

    if(a == b){
        return v[a];
    }
    
    m = (a + b)/2;
    left = Poli2(v, a, m, x);
    right = Poli2(v, m+1, b, x);

    return left + (right * expo(x, m-a+1));

}

int PoliHorner(int v[], int a, int b, int x){
    if(a > b){
        return 0;
    }

    return v[a] + x * PoliHorner(v, a+1, b, x);
}

int main(){
    srand(0);
    int n, x, fx, f1x, f2x;

    scanf("%d", &n);
    int v[n];

    gera_vetor(v, n);
    printf("Coeficientes do Polinômio: ");
    imprime_v(v, n);
    printf("Digite o valor de x:\n");
    scanf("%d", &x);
    fx = Pol(v, 0, n-1, x);
    printf("F(%d) = %d\n", x, fx);
    f1x = Poli2(v, 0, n-1, x);
    printf("F(%d) = %d\n", x, f1x);
    f2x = PoliHorner(v, 0, n-1, x);
    printf("F(%d) = %d\n", x, f2x);
    printf("X elevado a n: %d\n", expo(x, n));
    printf("X elevado a n: %d\n", expo2(x, n));

    return 0;
}