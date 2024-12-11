#include <bits/stdc++.h>
using namespace std;

int main (){
    int hora_ini, min_ini, hora_fim, min_fim, horas, minutos;
    cin >> hora_ini >> min_ini >> hora_fim >> min_fim;
    if ((hora_fim == hora_fim) && (min_ini == min_fim)){
        horas = 24;
        minutos = 0;
    }else{
        if (hora_fim > hora_ini){
            if (min_fim >= min_ini){
                horas = hora_fim - hora_ini;
                minutos = min_fim - min_ini;
            }else{
                horas = hora_fim - hora_ini - 1;
                minutos = 60 - min_ini + min_fim;
            }
        }else{
            if (min_fim >= min_ini){
                horas = 24 - hora_ini + hora_fim;
                minutos = min_fim - min_ini;
            }else{
                horas = 24 - hora_ini + hora_fim - 1;
                minutos = 60 - min_ini + min_fim;
            }
        }
        if (horas == 24){
            horas = 0;
        }
    }

    cout << "O JOGO DUROU " << horas << " HORA(S) E " << minutos << " MINUTO(S)\n";
}