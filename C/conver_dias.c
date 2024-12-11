#include <stdio.h>

int main (){
	int anos, meses, dias, total;
	printf ("Informe sua idade em anos, meses e dias respectivamente: ");
	scanf ("%d %d %d", &anos, &meses, &dias);
	total = (anos * 365) + (meses * 30) + dias;
	printf ("A idade dessa pessoa em dias é: %d\n", total);
}