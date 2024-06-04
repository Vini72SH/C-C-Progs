#include <stdio.h>

int main (){
	// Programa 1 (Número Triangular)
    /*
  	int num, mult;
	int cont = 1, linear = 0;
	scanf ("%d", &num);
	while ((mult <= num) && (linear == 0)){
		mult = cont * (cont + 1) * (cont + 2);
			if (mult == num){
				linear = 1;
			}
		cont++;
	}
	if (linear == 1){
		printf("%d\n", 1);
	}else{
		printf("%d\n", 0);
	}
	*/

	//Programa 2 (Valor quadrado)
	/*
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
	*/

	//Programa 3 (Número perfeito)
	/*
	int test, soma, num = 2, i = 1; 
	scanf ("%d", &test);
	while (i <= test){
		soma = 0;
		for (int j = 1; j <= num/2; j++){
			if (num % j == 0){
				soma = soma + j;
			}
		}
		if (soma == num){
			printf("%d\n", num);
			i++;
		}
		num++;
	}
	*/

	//Programa 4 (Metade ou Dobro)
	/*
	int num, num_ant;
	int soma = 0, cont = 0;
	scanf ("%d", &num_ant);
	cont++;
	soma+= num_ant;
	scanf ("%d", &num);
	cont++;
	soma += num;
	while ((num_ant != num*2) && (num_ant != num / 2)){
		num_ant = num;
		scanf("%d", &num);
		cont++;
		soma += num;
	}
	printf("%d ", cont);
	printf("%d ", soma);
	printf("%d ", num_ant);
	printf("%d\n", num);
	*/

	//Programa 5 (Multiplo de 37)
	/*
	int num, mult, soma, dig;
	scanf ("%d", &num);
	mult = num * 37;
	soma = 0;
	while (mult > 0){
		dig = mult % 10;
		soma += dig;
		mult = mult / 10;
	}
	if (num == soma){
		printf ("SIM\n");
	}else{
		printf ("NAO\n");
	}
	*/

	//Programa 6 (Fibonacci)
	/*
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
	*/

	//Programa 7 (Fatorial)
	/*
	int num, cont = 1, fat = 1;
	scanf ("%d", &num);
	while (cont <= num){
		fat = fat * cont;
		cont = cont + 1;
	}
	printf ("%d\n", fat);
	*/
}