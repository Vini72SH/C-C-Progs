#include <stdio.h>

int main (){
    float salario_min, salario, quantia;
    printf ("Digite o valo do salário mínimo: \n");
    scanf ("%f", &salario_min);
    printf ("Digite o seu salário: \n");
    scanf ("%f", &salario);
    quantia = salario / salario_min;

    printf ("Uma pessoa que recebe R$ %.2f reais, recebe %.1f salários mínimos. \n", salario, quantia);
}