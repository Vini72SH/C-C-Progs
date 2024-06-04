#include <stdio.h>

int main (){
	float peso, altura, IMC;
	printf ("Calculador de IMC!\n");
	printf ("Digite seu peso e sua altura: ");
	scanf ("%f %f", &peso, &altura);
	IMC = peso / (altura * altura);
	printf ("O IMC é: %.2f\n", IMC);
}