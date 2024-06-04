#include <stdio.h>

int main (){
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
}