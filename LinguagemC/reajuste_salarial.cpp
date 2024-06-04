#include <bits/stdc++.h>
using namespace std;

int main (){
    int percentual;
    double salario, novo_salario, reajuste, aumento;
    cin >> salario;
    if (salario <= 400.00){
        aumento = (salario * 15) / 100;
        novo_salario = salario + aumento;
        reajuste = novo_salario - salario;
        percentual = 15;
    }else if(salario <= 800.00){
            aumento = (salario * 12) / 100;
            novo_salario = salario + aumento;
            reajuste = novo_salario - salario;
            percentual = 12;
        }else if (salario <= 1200.00){
                aumento = (salario * 10) / 100;
                novo_salario = salario + aumento;
                reajuste = novo_salario - salario;
                percentual = 10;
            }else if (salario <= 2000.00){
                    aumento = (salario * 7) / 100;
                    novo_salario = salario + aumento;
                    reajuste = novo_salario - salario;
                    percentual = 7;
                }else{
                        aumento = (salario * 4) / 100;
                        novo_salario = salario + aumento;
                        reajuste = novo_salario - salario;
                        percentual = 4;
                    }
    printf ("Novo salario: %.2f\n", novo_salario);
    printf ("Reajuste ganho: %.2f\n", reajuste);
    cout << "Em percentual: " << percentual << " %\n";
}