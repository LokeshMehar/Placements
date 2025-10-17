#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> dp(n + 1, 0);
    dp[0] = 1; // empty subsequence
    unordered_map<int, int> last; // last occurrence index of each element

    for (int i = 1; i <= n; i++) {
        dp[i] = (2 * dp[i - 1]) % MOD;

        if (last.count(a[i])) {
            int j = last[a[i]];
            dp[i] = (dp[i] - dp[j - 1] + MOD) % MOD;
        }

        last[a[i]] = i;
    }

    cout << (dp[n] - 1 + MOD) % MOD << "\n"; // remove empty subsequence
    return 0;
}
