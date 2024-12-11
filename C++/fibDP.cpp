#include <iostream>
#include <vector>

using namespace std;

int fibonacci_dp(int n) {
    vector<int> fib(n+1);
    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i <= n; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return fib[n];
}

int main() {
    int n = 10;
    cout << "O " << n << "-ésimo número de Fibonacci é: " << fibonacci_dp(n) << '\n';
    return 0;
}