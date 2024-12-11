#include <stdio.h>

int main (){
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
}