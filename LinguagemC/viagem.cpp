#include <bits/stdc++.h>
using namespace std;

int main (){
    int tempo, vm;
    double litros;
    cin >> tempo >> vm;
    litros = tempo * vm;
    litros = litros / 12;
    printf ("%.3f\n", litros);
}