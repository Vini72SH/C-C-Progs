#include <bits/stdc++.h>
using namespace std;

int main (){
    string nome;
    double salario, montante, total;
    cin >> nome >> salario >> montante;
    total = salario + (montante * 15) / 100;
    cout << fixed << setprecision (2);
    cout << "TOTAL = R$ " << total << "\n";
}