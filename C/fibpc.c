#include <stdio.h>

int main(){
    int n, penult = 0, ult = 1, fib = 0;
    int cont = 0;

    scanf("%d", &n);

    if(cont == n){
        printf("Fib(%d) = %d\n", n, fib);
        return 0;
    }

    cont++;
    fib++;
    if(cont == n){
        printf("Fib(%d) = %d\n", n, fib);
        return 0;
    }

    cont++;
    while(cont < n){
        fib = ult + penult;
        printf("Fib(%d) = %d\n", cont, fib);
        penult = ult;
        ult = fib;
        cont++;
    }

    fib = ult + penult;
    printf("Fib(%d) = %d\n", cont, fib);

    return 0;   
}