#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 4;

    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int N = (1 << n);
    vector<vector<int>> dp(N, vector<int>(n, INT_MAX));

    dp[1][0] = 0; // start from city 0

    for(int mask = 1; mask < N; mask++) {
        for(int u = 0; u < n; u++) {
            if(!(mask & (1 << u))) continue;

            for(int v = 0; v < n; v++) {
                if(mask & (1 << v)) continue;

                dp[mask | (1 << v)][v] = min(
                    dp[mask | (1 << v)][v],
                    dp[mask][u] + dist[u][v]
                );
            }
        }
    }

    int ans = INT_MAX;

    for(int i = 1; i < n; i++) {
        ans = min(ans, dp[N-1][i] + dist[i][0]);
    }

    cout << "Minimum TSP cost = " << ans;
}