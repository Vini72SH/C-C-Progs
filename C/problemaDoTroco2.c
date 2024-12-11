#include <stdio.h>
#include <limits.h>

int min (int a, int b) {
    return (a < b) ? a : b;
}

int coinChange(int coins[], int m, int V) {
    int table[m+1][V+1];

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= V; ++j) {
            if (j == 0) {
                table[i][j] = 0;
            } else if (i == 0) {
                table[i][j] = INT_MAX;
            } else if (coins[i-1] <= j) {
                table[i][j] = min(table[i-1][j], 1 + table[i][j-coins[i-1]]); 
            } else {
                table[i][j] = table[i-1][j];
            }
        }
    }

    return table[m][V];
}

int main () {
    int coins[] = {1, 2, 5};
    int m = sizeof(coins)/sizeof(coins[0]);
    int V = 11;

    printf("Número mínimo de moedas: %d\n", coinChange(coins, m, V));

    return 0;
}