#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> p(n + 1);
        for (int i = 1; i <= n; i++) cin >> p[i];
        int l, r;
        cin >> l >> r;

        // Construct modified array a
        vector<int> a = p;
        for (int i = l; i <= r; i++) a[i]++;

        // Now we need to detect l and r as if we didn’t know them
        // ---- Offline detection logic ----
        int found_l = -1, found_r = -1;
        for (int i = 1; i <= n; i++) {
            if (a[i] != p[i]) {
                if (found_l == -1) found_l = i;
                found_r = i;
            }
        }

        cout << found_l << " " << found_r << "\n";
    }

    return 0;
}
