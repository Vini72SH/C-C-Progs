#include <bits/stdc++.h>
using namespace std;

int main (){
    double dinheiro;
    int contador = 0;
    cin >> dinheiro;
    cout << "NOTAS:\n";

    while (dinheiro >= 100){
        dinheiro -= 100;
        contador++;
    }
    cout << contador << " nota(s) de R$ 100.00\n";

    contador = 0;
    while (dinheiro >= 50){
        dinheiro -= 50;
        contador++;
    }
    cout << contador << " nota(s) de R$ 50.00\n";
    
    contador = 0;    
    while (dinheiro >= 20){
        dinheiro -= 20;
        contador++;
    }
    cout << contador << " nota(s) de R$ 20.00\n";

    contador = 0;
    while (dinheiro >= 10){
        dinheiro -= 10;
        contador++;
    }
    cout << contador << " nota(s) de R$ 10.00\n";

    contador = 0;
    while (dinheiro >= 5){
        dinheiro -= 5;
        contador++;
    }
    cout << contador << " nota(s) de R$ 5.00\n";

    contador = 0;
    while (dinheiro >= 2){
        dinheiro -= 2;
        contador++;
    }
    cout << contador << " nota(s) de R$ 2.00\n";
    
    cout << "MOEDAS:\n";

    contador = 0;    
    while (dinheiro >= 1){
        dinheiro -= 1;
        contador++;
    }
    cout << contador << " moeda(s) de R$ 1.00\n";

    dinheiro = dinheiro * 100;

    contador = 0;
    while (dinheiro >= 50){
        dinheiro -= 50;
        contador++;
    }
    cout << contador << " moeda(s) de R$ 0.50\n";
    
    contador = 0;
    while (dinheiro >= 25){
        dinheiro -= 25;
        contador++;
    }
    cout << contador << " moeda(s) de R$ 0.25\n";

    contador = 0;
    while (dinheiro >= 10){
        dinheiro -= 10;
        contador++;
    }
    cout << contador << " moeda(s) de R$ 0.10\n";
    
    contador = 0;
    while (dinheiro >= 5){
        dinheiro -= 5;
        contador++;
    }
    cout << contador << " moeda(s) de R$ 0.05\n";

    contador = 0;
    while (dinheiro >= 1){
        dinheiro -= 1;
        contador++;
    } 
    cout << contador << " moeda(s) de R$ 0.01\n";
}