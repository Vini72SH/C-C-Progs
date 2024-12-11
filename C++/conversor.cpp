#include <bits/stdc++.h>
using namespace std;

int main (){
    int segundos, seg, min, horas;
    cin >> segundos;
    seg = segundos % 60;
    min = segundos / 60;
    horas = min / 60;
    min = min % 60;
    cout << horas << ":" << min << ":" << seg << "\n"; 
}