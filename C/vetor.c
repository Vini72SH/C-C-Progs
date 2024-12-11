#include <stdio.h>
#define MAX 5

int ler (int v[]){
	int i, tam;
	scanf ("%d", &tam);
	if (tam > MAX)
		return -1;
	for (i = 0; i < tam; i++)
		scanf ("%d", &v[i]);
	return tam;
}

void imprimir_ao_contrario (int v[], int tam){
	int i;

	for (i = tam-1; i >= 0; i--)
		printf("%d", v[i]);
	printf ("\n");
}

int main (){
	int v[MAX], tam;
	if ((tam = ler(v)) < 0)
		return -1;
	imprimir_ao_contrario (v, tam);

	return 0;
}