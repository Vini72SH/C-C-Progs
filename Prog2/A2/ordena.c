#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordena.h"

void troca(int v[], int a, int b){
    int aux;

    aux = v[a];
    v[a] = v[b];
    v[b] = aux;
}

void inverte_vetor(int *aux, int tam){
    int a, b;

    a = 0;
    b = tam - 1;

    while(a < b){
        troca(aux, a, b);
        a++;
        b--;
    }
}

int comparaS(char *s1, char *s2){

    if(strcmp(s1, "NaN") == 0)
        return 1;

    if(strcmp(s2, "NaN") == 0)
        return 0;

    if(!(atoi(s1)) || !(atoi(s2))){
        return (strcmp(s1, s2) <= 0);
    }else{
        return (atof(s1) <= atof(s2));
    }

    return 0;        
}

void Merge(char **v, int ini, int meio, int fim, int *ind){
    int *L, *R;
    int i, j, k, n1, n2;

    n1 = meio - ini + 1;
    n2 = fim - meio;

    L = malloc(n1 * sizeof(int));
    R = malloc(n2 * sizeof(int));
    if(!(L) || !(R)) return;

    for(i = 0; i < n1; i++)
        L[i] = ind[ini + i];
    for(j = 0; j < n2; j++)
        R[j] = ind[meio + 1 + j];

    i = 0;
    j = 0;
    k = ini;

    while((i < n1) && (j < n2)){
        if (comparaS(v[L[i]], v[R[j]])){
            ind[k] = L[i];
            i++;
        }else{
            ind[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        ind[k] = L[i];
        i++;
        k++;
    }

    while (j < n2){
        ind[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void Merge_Sort(char **v, int ini, int fim, int *ind){
    int meio;

    if (ini < fim){
        meio = (fim + ini) / 2;
        Merge_Sort(v, ini, meio, ind);
        Merge_Sort(v, meio+1, fim, ind);
        Merge(v, ini, meio, fim, ind);
    }
}