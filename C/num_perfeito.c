#include <stdio.h>

int main (){
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
}