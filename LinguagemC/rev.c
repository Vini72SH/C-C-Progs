#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void troca (int v[], int a, int b){
	int aux;

	aux = v[a];
	v[a] = v[b];
	v[b] = aux;
}

void gera_vetor (int v[], int tam){
	int i;

	for (i = 0; i < tam; i++){
		v[i] = (rand () % 100)+1;
	}
}

void imprime_v (int v[], int tam){
	int i;

	for (i = 0; i < tam; i++){
		printf ("%d ", v[i]);
	}
	printf ("\n");
}

void rev (int v[], int a, int b){
	if (a >= b){

		return;
	}

	troca (v, a, b);
	return rev (v, a+1, b-1);
}

int main (){
	int a, b;

	srand (0);
	a = 0;
	scanf("%d", &b);
	int v[b];
	
	gera_vetor (v, b);
	imprime_v(v, b);
	rev (v, a, b-1);
	imprime_v (v, b);
}