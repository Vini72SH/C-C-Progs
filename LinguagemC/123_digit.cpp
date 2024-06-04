#include <bits/stdc++.h>
using namespace std;

int main (){
    int n, d, d_prox;
    bool check = true;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    cin >> n;

    if (n < 10){
        cout << "Yes" << "\n";

        return 0;
    }
    
    d = n % 10;
    n = n / 10;

    while ((check) && (n > 0)){
        d_prox = n % 10;
        n = n / 10;
        if (d >= d_prox){
            check = false;
        }
        d = d_prox;
    }
    
    if (check){
        cout << "Yes" << "\n";
    }else{
        cout << "No" << "\n";
    }
    
    return 0;
}

