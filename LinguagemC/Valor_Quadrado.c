#include <stdio.h>

int main (){
	int num1, num2;
	int valor = 1;

	scanf ("%d", &num1);
	while (num1 != 0){
		scanf ("%d", &num2);
		if (num2 != num1*num1){
			valor = 0;
		}
		scanf ("%d", &num1);
	}
	printf ("%d\n", valor);
}