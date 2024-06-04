#include <stdio.h>

int main (){
	float valor, novo_valor;
	printf ("Informe o preço atual do produto: ");
	scanf ("%f", &valor);
	novo_valor = valor - (valor * 0.1);
	printf("O novo preço do produto é: R$ ");
	printf("%.2f\n", novo_valor);
}