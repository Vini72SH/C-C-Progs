#include <bits/stdc++.h>
using namespace std;

int main (){
    double A, B, C, Area, Perimetro;
    cin >> A >> B >> C;
    cout << fixed << setprecision(1);
    if (((abs(B - C) < A) && (A < B + C)) || ((abs(A - C) < B) && (B < A + C)) || ((abs(A - B) < C) && (C < A + B))){
        Perimetro = A + B + C;
        cout << "Perimetro = " << Perimetro << "\n";
    }else{
        Area = ((A + B) * C) / 2;
        cout << "Area = " << Area << "\n";
    }
}