#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void troca(int v[], int a, int b){
	int aux;

	aux = v[a];
	v[a] = v[b];
	v[b] = aux;
}

void gera_vetor(int v[], int tam){
	int i;

	for (i = 0; i < tam; i++){
		v[i] = rand() % tam+1;
	}
}

void imprime_v(int v[], int tam){
	int i;

	for(i = 0; i < tam; i++){
		printf("%d ", v[i]);
	}
	printf("\n");
}

int minimo(int v[], int a, int b){
	int m;

	if (a == b){
		return a;
	}

	m = minimo(v, a, b-1);
	if (v[b] < v[m]){
		return b;
	}
	
	return m;
}

void Selection_Sort(int v[], int a, int b){
	int m;

	if(a >= b){
		return;
	}
	m = minimo(v, a, b);
	troca(v, a, m);
	Selection_Sort(v, a+1, b);
}

void Selection_Sort_It(int v[], int a, int b){
	int i, j, min_idx;

	for(i = a; i < b; i++){
		min_idx = i;
		for(j = i+1; j <= b; j++){
			if(v[j] < v[min_idx]){
				min_idx = j;
			}
		}
		if(min_idx != i){
			troca(v, i, min_idx);
		}
	}
}


int BuscaBin(int x, int v[], int a, int b){
	int m;

	if (a > b)
		return a-1;

	m = (a + b)/2;
	if (v[m] <= x)
		return BuscaBin(x, v, m+1, b);
	return BuscaBin(x, v, a, m-1);
}

void Insere(int v[], int a, int b){
	int p, i;

	p = BuscaBin(v[b], v, a, b-1)+1;
	i = b;
	while (i > p){
		troca(v, i-1, i);
		i--;
	}
}

void Insertion_Sort_Rec(int v[], int a, int b){
	if (a >= b)
		return;
	Insertion_Sort_Rec(v, a, b-1);
	Insere(v, a, b);
}

void Insertion_Sort(int v[], int a, int b){
	if (a >= b)
    	return;

    Insertion_Sort(v, a, b - 1);

    int chave = v[b];
    int j = b - 1;

    while (j >= a && v[j] > chave) {
        v[j + 1] = v[j];
        j--;
    }

    v[j + 1] = chave;
}

void Merge(int v[], int a, int meio, int b){
	int i, j, k, n1, n2;

	n1 = meio - a + 1;
	n2 = b - meio;

	int L[n1];
	int R[n2];

	for(i = 0; i < n1; i++)
		L[i] = v[a + i];
	for(j = 0; j < n2; j++)
		R[j] = v[meio + 1 + j];

	i = 0;
	j = 0;
	k = a;

	while((i < n1) && (j < n2)){
		if (L[i] <= R[j]){
			v[k] = L[i];
			i++;
		}else{
			v[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1){
		v[k] = L[i];
		i++;
		k++;
	}

	while (j < n2){
		v[k] = R[j];
		j++;
		k++;
	}
}

void Merge_Sort(int v[], int a, int b){
	int meio;

	if (a < b){
		meio = (b  + a) / 2;
		Merge_Sort(v, a, meio);
		Merge_Sort(v, meio+1, b);
		Merge(v, a, meio, b);
	}
}

int Maior_Filho(int v[], int i, int k){
    int maior, e, d;

    maior = i;
    e = 2 * i + 1;
    d = 2 * i + 2;
    
    if (e < k && v[e] > v[maior]){
        maior = e;
    }

    if (d < k && v[d] > v[maior]){
        maior = d;
    }

    return maior;
}

void ConcertaHeap(int v[], int i, int k){
    int maior;

    maior = Maior_Filho(v, i, k);
    if (maior != i){
        troca(v, i, maior);
        ConcertaHeap(v, maior, k);
    }
}

void MontaHeap(int v[], int k){
    int i;

    for(i = k/2 - 1; i >= 0; i--){
        ConcertaHeap(v, i, k);
    }
}

void Heap_Sort (int v[], int a, int b){
    int n, k;

    n = b - a + 1;
    MontaHeap(v, n);

    for(k = n-1; k > 0; k--){
        troca(v, 0, k);
        ConcertaHeap(v, 0, k);
    }
}

int particionar(int v[], int a, int b, int x) {
    int i = a - 1;

    for (int j = a; j <= b - 1; j++) {
        if (v[j] < x) {
            i++;
            troca(v, i, j);
        }
    }

    troca(v, i + 1, b);
    return (i + 1);
}

void Quick_Sort(int v[], int a, int b) {
    if (a < b) {
        int m = particionar(v, a, b, v[b]);

        Quick_Sort(v, a, m - 1);
        Quick_Sort(v, m + 1, b);
    }
}

int main (){
	srand(0);
	clock_t ini, fim;
	double total;
	int n, op;

	printf("Super Programa Master Testador de Algoritmos de Ordenação!\n");
	printf("Digite o tamanho do vetor:\n");
	scanf("%d", &n);
	printf("Criando um vetor de tamanho %d que será preenchido com valores entre 0 e %d!\n", n, n);

	int vetor[n];

	gera_vetor(vetor, n);

	printf("Impressão do vetor:\n");
	imprime_v(vetor, n);

	printf("Selecione o Algoritmo de Ordenação:\n");
	printf("1 - Selection Sort (Recursivo)\n2 - Selection Sort (Iterativo)\n");
	printf("3 - Insertion Sort (Iterativo)\n4 - Insertion Sort (c/ Busca Binária)\n5 - Merge Sort\n6 - Heap Sort\n");
	printf("7 - Quick Sort\nOp:");
	scanf("%d", &op);

	switch(op){
	case 1:
		ini = clock();
		Selection_Sort(vetor, 0, n-1);
		fim = clock();
		break;
	case 2:
		ini = clock();
		Selection_Sort_It(vetor, 0, n-1);
		fim = clock();
		break;
	case 3:
		ini = clock();
		Insertion_Sort(vetor, 0, n-1);
		fim = clock();
		break;
	case 4:
		ini = clock();
		Insertion_Sort_Rec(vetor, 0, n-1);
		fim = clock();
		break;
	case 5:
		ini = clock();
		Merge_Sort(vetor, 0, n-1);
		fim = clock();
		break;
    case 6:
        ini = clock();
        Heap_Sort(vetor, 0, n-1);
        fim = clock();
        break;
    case 7:
    	ini = clock();
    	Quick_Sort(vetor, 0, n-1);
    	fim = clock();
    	break;
    default:
    	printf("Opção Inválida.");
	}

	total = ((double)fim - ini)/CLOCKS_PER_SEC;

	printf("Impressão do vetor ordenado:\n");
	imprime_v(vetor, n);

	printf("Tempo total de execução: %f\n", total);

	return 0;
}