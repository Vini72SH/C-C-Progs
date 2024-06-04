#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void gera_vetor (int v[], int tam){
	int i;

	for (i = 0; i < tam; i++){
		v[i] = rand() % 101;
	}
}

void imprime_vetor (int v[], int tam){
	int i;

	for (i = 0; i < tam; i++){
		printf ("%d ", v[i]);
	}
	printf("\n");
}

void Insertion_Sort (int v[], int tam){
	int i, j, chave;
	for (i = 1; i < tam; i++){
		chave = v[i];
		j = i - 1;
		while ((j >= 0) && (v[j] > chave)){
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = chave;
	}
}

void troca (int v[], int a, int b){
	int x;

	x = v[a];
	v[a] = v[b];
	v[b] = x;
}

void Inverte_vetor (int v[], int a, int b, int *cont){
	if (a >= b)
		return;

	troca (v, a, b);

	(*cont)++;

	return Inverte_vetor (v, a+1, b-1, cont);
}

int main (){
	srand (0);
	int a = 0, cont = 0;
	int tam = 15;
	int v[tam];

	gera_vetor (v, tam);
	printf ("Vetor Não Ordenado:\n");
	imprime_vetor (v, tam);

	Insertion_Sort (v, tam);
	printf ("Vetor Ordenado:\n");
	imprime_vetor (v, tam);

	Inverte_vetor (v, a, tam-1, &cont);
	printf ("Vetor Invertido:\n");
	imprime_vetor (v, tam);

	printf ("# de trocas feitas: %d\n", cont);
}