#include <bits/stdc++.h>
using namespace std;

int main (){
    int A, B, C, D;
    bool valores;
    cin >> A >> B >> C >> D;
    if (((B > C) && (D > A)) && ((C + D) > (A + B)) && ((C > 0) && (D > 0)) && (A % 2 == 0)){
        valores = true;
    }else{
        valores = false;
    }

    if (valores == true){
        cout << "Valores aceitos\n";
    }else{
        cout << "Valores nao aceitos\n";
    }
}