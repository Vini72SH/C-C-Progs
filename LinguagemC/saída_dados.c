#include <stdio.h>
#define texto "Entrada e saída de dados"


int main (){

    printf("%s\n", texto);

    int idade = 0;
    float altura = 0.0;
    char nome [50] = "";

    printf ("Digite sua idade: \n");
    scanf ("%d", &idade);
    printf ("Digite sua altura: \n");
    scanf ("%f", &altura);
    printf ("Digite seu nome: \n");
    scanf ("%s", nome);

    printf ("Seu nome é: %s.\n", nome);
    printf ("Sua idade é: %d.\n", idade);
    printf ("E sua altura é: %.2f.\n", altura);
}