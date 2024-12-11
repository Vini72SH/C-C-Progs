#include <bits/stdc++.h>
using namespace std;

int main (){
    int n1, n2, n3, maior, medio, menor;
    cin >> n1 >> n2 >> n3;

    if (n1 > n2){
        if (n1 > n3){
            maior = n1;
            if (n3 > n2){
                menor = n2;
                medio = n3;
            }else{
                menor = n3;
                medio = n2;
            }
        }else{
            maior = n3;
            medio = n1;
            menor = n2;
        }
    }else{
        if (n2 > n3){
            maior = n2;
            if (n3 > n1){
                menor = n1;
                medio = n3;
            }else{
                menor = n3;
                medio = n1;
            }
        }else{
            maior = n3;
            medio = n2;
            menor = n1;
        }
    }

    cout << menor << '\n';
    cout << medio << '\n';
    cout << maior << '\n';
    cout << '\n';
    cout << n1 << '\n';
    cout << n2 << '\n';
    cout << n3 << '\n';
}