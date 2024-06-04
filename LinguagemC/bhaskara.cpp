#include <bits/stdc++.h>
using namespace std;

int main(){
    double A, B, C, x1, x2, delta;
    cin >> A >> B >> C;
    delta = B * B -4 * A * C;
    if ((A != 0) && (delta >= 0)){
        x1 = (-B + sqrt (delta)) / (2*A);
        x2 = (-B - sqrt (delta)) / (2*A);
        cout << fixed << setprecision (5);
        cout << "R1 = " << x1 << "\n";
        cout << "R2 = " << x2 << "\n";
    }else{
        cout << "Impossivel calcular\n";
    }
}