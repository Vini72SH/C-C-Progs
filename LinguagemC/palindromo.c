#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gera_vetor (int v[], int tam){
	int i;

	for (i = 0; i < tam; i++){
		scanf ("%d", &v[i]);
	}

	return;

}

int testa_palindromo (int v[], int a, int b){
	if (a > b){
		return 1;
	}
	if (v[a] == v[b]){
		return testa_palindromo (v, a+1, b-1);
	}else{
		return 0;
	}
}

int main (){
	int a = 0, b;
	srand (0);

	scanf ("%d", &b);
	int v[b];
	gera_vetor (v, b);

	if (testa_palindromo (v, a, b-1)){
		printf ("É um palíndromo.\n");
	}else{
		printf ("Não é um palíndromo\n");
	}

	return 0;
}