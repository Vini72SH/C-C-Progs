#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<int, int>memo;

int fibonacci_memo(int n) {
    if (memo.count(n)) {
        return memo[n];
    }

    if (n <= 1) {
        return n;
    }

    memo[n] = fibonacci_memo(n - 1) + fibonacci_memo(n - 2);
    return memo[n];
}

int main () {
    int n = 10;
    cout << "O " << n << "-ésimo número de Fibonacci é: " << fibonacci_memo(n) << '\n';

    return 0;
}