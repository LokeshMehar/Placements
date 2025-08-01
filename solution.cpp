#include <bits/stdc++.h>
using namespace std;

long getMaximumGrossValue(int arr_count, int* arr) {
    int n = arr_count;
    vector<long long> p(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        p[i + 1] = p[i] + arr[i];
    }

    // Precompute max p[i_val] for 0 <= i_val <= j
    vector<long long> maxPI(n + 1);
    maxPI[0] = p[0];
    for (int j = 1; j <= n; ++j) {
        maxPI[j] = std::max(maxPI[j - 1], p[j]);
    }

    // Precompute max p[k_val] for j <= k_val <= n
    vector<long long> maxPK(n + 1);
    maxPK[n] = p[n];
    for (int j = n - 1; j >= 0; --j) {
        maxPK[j] = std::max(maxPK[j + 1], p[j]);
    }

    long long maxGrossValue = LLONG_MIN;

    for (int j = 0; j <= n; ++j) {
        long long currentGrossValue = maxPI[j] - p[j] + maxPK[j];
        maxGrossValue = std::max(maxGrossValue, currentGrossValue);
    }

    return maxGrossValue;
}

int main() {
    // Test with the given examples
    int arr1[] = {-1,1,-2,-2};
    cout << getMaximumGrossValue(4, arr1) << endl; // Expected: 6
    
    int arr2[] = {4, -8, 2, -10, 3, -20};
    cout << getMaximumGrossValue(6, arr2) << endl; // Expected: 43
    
    return 0;
}