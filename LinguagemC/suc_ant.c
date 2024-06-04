#include <stdio.h>

int main (){
	int num, ant, suc;
	printf ("Digite um valor inteiro: ");
	scanf ("%d", &num); 
	ant = num - 1;
	suc = num + 1;
	printf ("Antecessor = %d\nSucessor = %d\n", ant, suc);
}