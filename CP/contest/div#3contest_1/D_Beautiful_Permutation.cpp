#include <bits/stdc++.h>
using namespace std;
#define ln '\n'
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        vector<int> p(n + 2);
        for (int i = 1; i <= n; i++) cin >> p[i];
        int l, r;
        cin >> l >> r;

        vector<int> a = p;
        // Correct modification: shift values instead of increment
        for (int i = l; i <= r; i++) {
            if (i + 1 <= n)
                a[i] = p[i + 1];
        }

        int found_l = -1, found_r = -1;
        for (int i = 1; i <= n; i++) {
            if (a[i] != p[i]) {
                if (found_l == -1) found_l = i;
                found_r = i;
            }
        }

        // Output in expected format
        cout << "1 " << found_l << " " << found_r << ln;
        cout << "2 " << found_l << " " << found_r << ln;
        cout << "! " << found_l << " " << found_r << ln;
    }

    return 0;
}
