#include <bits/stdc++.h>
using namespace std;

int main (){
    int A, B;
    cin >> A >> B;
    if ((B % A == 0) || (A % B == 0)){
        cout << "Sao Multiplos\n";
    }else{
        cout << "Nao sao Multiplos\n";
    }
}