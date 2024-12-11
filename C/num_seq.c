#include <stdio.h>

int main (){
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
}