#include <stdio.h>

int main (){
	float base, altura, area;
	printf ("Informe os valores da base e da altura: ");
	scanf ("%f %f", &base, &altura);
	area = base * altura;
	printf ("O valor da área é: %.2f\n", area);
}