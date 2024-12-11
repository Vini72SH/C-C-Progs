#include <bits/stdc++.h>
using namespace std;

int main (){
    int num, quant;
    float total;
    cin >> num >> quant;
    if (num == 1){
        total = quant * 4.00; 
    }else if(num == 2){
        total = quant * 4.50;
        }else if(num == 3){
            total = quant * 5.00;
            }else if(num == 4){
                total = quant * 2.00;
                }else if(num == 5){
                    total = quant * 1.50;
                }
    cout << fixed << setprecision (2);
    cout << "Total: R$ " << total << "\n";
}