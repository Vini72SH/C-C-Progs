#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 16
#define MAX 100

void imprime_v(int v[], int tam){
    int i;

    for(i = 0; i < tam; i++){
        printf("%d ", v[i]);
    }
    printf("\n");

}
void gera_vetor(int v[], int tam){
    int i, n;

    for(i = 0; i < tam; i++){
        n = rand() % MAX+1;
        v[i] = n;
    }
}

void troca(int v[], int a, int b){
    int aux;

    aux = v[a];
    v[a] = v[b];
    v[b] = aux;
}

int Minimo(int v[], int a, int b){
    int m, i;

    m = a;
    for(i = a+1; i <= b; i++){
        if(v[i] < v[m]){
            m = i;
        }
    }

    return m;
}

int BuscaBin(int x, int v[], int a, int b){
    int m;

    if(a > b){
        return a - 1;
    }

    m = (a + b)/2;
    if(v[m] <= x){
        return BuscaBin(x, v, m+1, b);
    }
    
    return BuscaBin(x, v, a, m-1);
}

/* Retorna o pai ou o maior filho de um nodo i */
int Maior_Filho(int v[], int i, int k){
    int maior, e, d;

    maior = i;
    e = 2 * i + 1;
    d = 2 * i + 2;

    if((e < k) && (v[e] > v[maior])){
        maior = e;
    }

    if((d < k) && (v[d] > v[maior])){
        maior = d;
    } 

    return maior;
}

/* Concerta o heap apartir de um nodo i.
   E concerta os nodos inferiores da árvore. */
void ConcertaHeap(int v[], int i, int k){
    int maior;

    maior = Maior_Filho(v, i, k);
    if(maior != i){
        troca(v, i, maior);
        ConcertaHeap(v, maior, k);
    }
}

/*Separa a parte válida (k/2) e monta
  o heap apartir disso até o primeiro nodo.*/
void MontaHeap(int v[], int k){
    int i;

    for(i = k/2 - 1; i >= 0; i--){
        ConcertaHeap(v, i, k);
    }
}

void HeapSort(int v[], int a, int b){
    int n, k;

    n = b - a + 1;
    MontaHeap(v, n);
    printf("Heap Montado: ");

    for(k = n - 1; k > 0; k--){
        imprime_v(v, TAM);        
        troca(v, 0, k);
        ConcertaHeap(v, 0, k);
    }
}

void Merge(int v[], int a, int m, int b){
    int i, j, k;
    int n1 = m - a + 1;
    int n2 = b - m;

    int L[n1];
    int R[n2];

    for(i = 0; i < n1; i++){
        L[i] = v[a + i];
    }

    for(j = 0; j < n2; j++){
        R[j] = v[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = a;

    while((i < n1) && (j < n2)){
        if(L[i] <= R[j]){
            v[k] = L[i];
            i++;
        }else{
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        v[k] = L[i];
        i++;
        k++;
    }

    while(j < n2){
        v[k] = R[j];
        j++;
        k++;
    }
}

void Merge_Sort(int v[], int a, int b){
    int m;

    if(a < b){
        m = a + (b - a)/2;
        Merge_Sort(v, a, m);
        Merge_Sort(v, m + 1, b);
        Merge(v, a, m, b);
    }
}

void Selection_Sort(int v[], int a, int b){
    int m;

    if(a == b){
        return;
    }

    m = Minimo(v, a, b);
    troca(v, a, m);
    Selection_Sort(v, a+1, b);
}

void Insere(int v[], int a, int b){
    int p, i;

    p = BuscaBin(v[b], v, a, b)+1;
    i = b;
    while(i > p){
        troca(v, i, i-1);
        i--;
    }
}

void Insertion_Sort(int v[], int a, int b){
    if(a >= b){
        return;
    }
    Insertion_Sort(v, a, b-1);
    Insere(v, a, b);
}

int main(){
    srand(0);
    int v[TAM];

    gera_vetor(v, TAM);
    imprime_v(v, TAM);

    //HeapSort(v, 0, TAM-1);
    //Merge_Sort(v, 0, TAM-1);
    //Selection_Sort(v, 0, TAM-1);
    Insertion_Sort(v, 0, TAM-1);

    printf("%d\n", BuscaBin(95, v, 0, TAM-1));

    imprime_v(v, TAM);

    return 0;
}