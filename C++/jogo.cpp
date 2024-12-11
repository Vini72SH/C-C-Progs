#include <bits/stdc++.h>
using namespace std;

int main(){
    int hora_inicial, hora_final, Tempo;
    cin >> hora_inicial >> hora_final;
    if (hora_inicial < hora_final){
        Tempo = hora_final - hora_inicial;
    }else if(hora_inicial == hora_final){
        Tempo = 24;
        }else if(hora_inicial > hora_final){
            Tempo = 24 - hora_inicial + hora_final;
        }
    cout << "O JOGO DUROU " << Tempo << " HORA(S)\n";
}