#include <bits/stdc++.h>
using namespace std;

int Minimo (int v[], int a, int b){
    int m; 
    if (a == b)
        return a;
    m = Minimo (v, a, b-1);
    if (v[b] < v[m])
        return b;
    return m;
}   

void troca(int v[], int a, int b){
    int aux;
    
    if (v[a] != v[b]){
        aux = v[a];
        v[a] = v[b];
        v[b] = aux;
    }
}

void Ordena (int v[], int a, int b){
    int m;

    if (a >= b)
        return;
    m = Minimo (v, a, b);
    troca (v, a, m);
    Ordena (v, a+1, b);
}

int main (){
    int n, x, tam, chave, j, soma = 0;

    cin >> n >> x;
    tam = n-1;

    int v[tam];
    for (int i = 0; i < tam; i++){
        cin >> v[i];
    }
    
    Ordena (v, 0, tam-1);

    if (n <= 3){
        soma = v[n-2];
    }else{
        for (int i = 1; i < tam-1; i++){
            soma += v[i];
        }
    }
    
    if (soma - x >= 0){
        cout << 0 << "\n";
        return 0;
    }
    
    if (x - soma <= 100){
        cout << x - soma << "\n";
        return 0;
    }

    if (x - soma > 100){
        cout << -1 << "\n";
        return 0;
    }

    return 0;
}
