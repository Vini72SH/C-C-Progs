#include <stdio.h>

int main (){
	int num, cont = 1, fat = 1;
	scanf ("%d", &num);
	while (cont <= num){
		fat = fat * cont;
		cont = cont + 1;
	}
	printf ("%d\n", fat);
}