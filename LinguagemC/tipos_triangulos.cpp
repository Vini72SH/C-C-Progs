#include <bits/stdc++.h>
using namespace std;

int main (){
    double A, B, C, Maior, Medio, Menor;
    cin >> A >> B >> C;
    if (A > B){
        if (A > C){
            Maior = A;
            if (B > C){
                Medio = B;
                Menor = C;
            }else{
                Medio = C;
                Menor = B;
            }
        }else{
            Maior = C;
            Medio = A;
            Menor = B;
        }
    }else{
        if (B > C){
            Maior = B;
            if (A > C){
                Medio = A;
                Menor = C;
            }else{
                Medio = C;
                Menor = A;
            }
        }else{
            Maior = C;
            Medio = B;
            Menor = A;
        }
    }
    if (Maior >= Medio + Menor){
        cout << "NAO FORMA TRIANGULO\n";
    }else{
        if (Maior*Maior == Medio*Medio + Menor*Menor){
            cout << "TRIANGULO RETANGULO\n";
        }
        if (Maior*Maior > Medio*Medio + Menor*Menor){
            cout << "TRIANGULO OBTUSANGULO\n";
        }
        if (Maior*Maior < Medio*Medio + Menor*Menor){
            cout << "TRIANGULO ACUTANGULO\n";
        }
        if ((A == B) && (A == C)){
            cout << "TRIANGULO EQUILATERO\n";
        }
        if (((A == B) && (A != C)) || ((A == C) && (A != B)) || ((B == C) && (B != A))){
            cout << "TRIANGULO ISOSCELES\n";
        }
    }
}