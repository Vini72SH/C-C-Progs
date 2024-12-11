#include <stdio.h>

int main (){
	int num, cont, fib, ult, penult;
	scanf ("%d", &num);
	penult = 0;
	ult = 1;
	cont = 2;
	printf ("%d", penult);
	printf (", %d", ult);
	while (cont <= num){
		fib = ult + penult;
		penult = ult;
		ult = fib;
		printf(", %d ", fib);
		cont++;
	}
	printf ("\n");
}