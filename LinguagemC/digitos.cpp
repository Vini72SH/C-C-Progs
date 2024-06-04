#include <bits/stdc++.h>
using namespace std;

int main(){
    cout << "Programa contador de Digítos. Encerra ao ler dois 0's. \n";
    int A, B;
    cin >> A >> B;
    while ((A != 0) && (B != 0)){
    int cont;
    cont = B*log10(A) + 1;
    cout << "O número de dígitos é: \n";
    cout << cont << "\n";
    cin >> A >> B;
    }
}