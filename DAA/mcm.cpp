#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> arr = {1, 2, 3, 4}; // example
    int n = arr.size();

    vector<vector<int>> dp(n, vector<int>(n, 0));

    for(int len = 2; len < n; len++) { // chain length
        for(int i = 1; i < n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;

            for(int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] 
                         + arr[i-1] * arr[k] * arr[j];

                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    cout << "Minimum multiplications = " << dp[1][n-1];
}