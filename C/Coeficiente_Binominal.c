#include <stdio.h>

int Fat(int n){
    if(n <= 1)
        return 1;

    return n * Fat(n - 1);
}

int Fat_d (int n, int k){
    if(k == 0)
        return 1;

    return n * Fat_d(n-1, k-1);
}


int CoefBin(int n, int k){
    int Coef;

    if(n < k){
        return 0;
    }

    Coef = Fat(n) / (Fat(k) * Fat(n - k));

    return Coef;
}

int CoefBin2(int n, int k){
    int Coef;

    if(n < k){
        return 0;
    }

    Coef = Fat_d(n, k) / Fat(k);

    return Coef;
}

int CoefBin3(int n, int k){
    if((n < k) || (k < 0)){
        return 0;
    }

    return (n / k)*CoefBin(n-1, k-1);
}

int main (){
    int n, k, cb, cb2;

    printf("Digite um N e um K:");
    scanf("%d %d", &n, &k);
    printf("Calculando o Coeficiente Binominal...\n");
    cb = CoefBin(n, k);
    printf("Coeficiente Binominal: %d\n", cb);
    cb2 = CoefBin2(n, k);
    printf("Com fatorial descendente: %d\n", cb2);
    printf("CB3 = %d\n", CoefBin3(n, k));

    return 0;
}