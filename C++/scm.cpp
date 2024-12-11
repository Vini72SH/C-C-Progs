#include <iostream>
#include <vector>

using namespace std;

int scm(vector<int> x) {
    int n = x.size();
    vector<int> r (n, 1);

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (x[i] > x[j]) {
                r[i] = (r[i] > 1 + r[j]) ? r[i] : 1 + r[j];
            }
        }
    }

    int maior = 0;
    for (int i = 0; i < r.size(); ++i) {
        if (r[i] > maior) {
            maior = r[i];
        }
    }

    return maior;
}

int main () {
    vector<int> x = {5, 2, 8, 9, 6, 3, 6, 10, 4};

    cout << "SCM: " << scm(x) << '\n';

    return 0;
}