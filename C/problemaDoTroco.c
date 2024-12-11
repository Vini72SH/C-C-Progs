#include <stdio.h>
#include <limits.h>

int min (int a, int b) {
    return (a < b) ? a : b;
}

int coinChange(int coins[], int m, int V) {
    int dp[V+1];

    dp[0] = 0;
    for (int i = 1; i <= V; ++i) {
        dp[i] = INT_MAX;
    }

    for (int i = 1; i <= V; ++i) {
        for (int j = 0; j < m; ++j) {
            if (coins[j] <= i) {
                dp[i] = min(dp[i], 1 + dp[i - coins[j]]);
            }
        }
    }
    return dp[V];
}

int main () {
    int coins[] = {1, 2, 5, 10};
    int m = sizeof(coins)/sizeof(coins[0]);
    int V = 278;

    printf("Número mínimo de moedas: %d\n", coinChange(coins, m, V));
    return 0;
}