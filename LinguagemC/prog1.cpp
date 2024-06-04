#include <iostream>
#include <cmath>

using namespace std;

#define ll long long
#define endl '\n'

bool is_prime(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;  // Early termination
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        bool v = 0;
        ll n, x, y;
        cin >> n;

        y = n/2 + 2;
        x = n/2 - 1;
        
        if((!(is_prime(x)) && (!(is_prime(y)))) && (x + y == n)) v = 1;

        if(v)
            cout << x << ' ' << y << '\n';
        else 
            cout << -1 << '\n';

    }

    return 0;
}