#include <stdio.h>

int main (){
    int A, B, soma, subt, mult, divis;

    printf ("Digite dois valores: \n");
    scanf ("%d", &A);
    scanf ("%d", &B);

    soma = A + B;
    subt = A - B;
    mult = A * B;
    divis = A / B;

    printf ("RESULTADOS: \n");
    printf ("Soma de A e B: %d.\n", soma);
    printf ("Subtração de A e B: %d.\n", subt);
    printf ("Multiplicação de A e B: %d.\n", mult);
    printf ("Divisão de A e B: %d.\n", divis);
}