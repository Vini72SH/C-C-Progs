#include <stdio.h>

int main (){
	int varA = 10, varB = 20, aux;
	aux = varA;
	varA = varB;
	varB = aux;
	printf ("O valor de A é: %d e o valor de B é: %d\n", varA, varB);
}