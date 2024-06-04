#include <stdio.h>

int multiplica (int a, int b){
	if ((a == 0) || (b == 0)){
		return 0;
	}else if (b == 1){
		return a;
	}else{
		return (a + multiplica(a, b - 1));
	}
}

int fat (int a){
	if (a == 0){
		return 0;
	}else if (a == 1){
		return a;
	}else{
		return (a * fat (a-1));
	}
}

int expo (int a, int b){
	if (b == 0){
		return 1;
	}else if (b == 1){
		return a;
	}else{
		return (a * expo (a, b-1));
	}
}

int fib (int n){
	if ((n == 0) || (n == 1)){
		return 1;
	}else{
		return fib(n - 1) + fib (n - 2);	
	}
}

int main (){
	int func, num1, num2, result;

	printf ("----- Programa de Recursividade -----\n");
	printf (" 1: Multiplicação.\n 2: Fatorial.\n 3: Exponenciação.\n 4: Fibonacci. \n Selecione a função: ");
	scanf("%d", &func);
	if (func == 1){ /*Calcula uma múltiplicação de forma recursiva*/
		printf ("Multiplicação Selecionada!\n");
		printf ("Digite dois números para serem multiplicados:\n");
		scanf ("%d %d", &num1, &num2);
		result = multiplica (num1, num2);
		printf ("O resultado da sua multiplicação é: %d.\n", result);

	}else if (func == 2){ /*Calcula a fatoração de forma recursiva*/
		printf ("Fatoração Selecionada!\n");
		printf ("Digite um número para calcular seu fatorial:\n");	
		scanf ("%d", &num1);
		result = fat (num1);
		printf ("O resultado do fatorial de %d é: %d.\n", num1, result);

	}else if (func == 3){ /*Calcula a exponenciação de forma recursiva*/
		printf ("Exponenciação Selecionada!\n");
		printf ("Digite a base e o expoente:\n");	
		scanf ("%d %d", &num1, &num2);
		result = expo (num1, num2);
		printf ("O resultado da exponenciação de %d por %d é: %d.\n", num1, num2, result);

	}else if(func == 4){ /*Calcula o Fibonacci de forma recursiva.*/
		printf ("Sequência de Fibonacci!\n");
		printf ("Digite um número n para que seja calculado fib(n): ");
		scanf ("%d", &num1);
		result = fib(num1);
		printf ("O fibonacci desse número é: %d.\n", result);
	}
	return 0;
}