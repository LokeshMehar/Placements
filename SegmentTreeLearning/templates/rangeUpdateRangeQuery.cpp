#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
long long seg[4 * N], lazy[4 * N];
int arr[N];

void build(int idx, int low, int high) {
    if (low == high) {
        seg[idx] = arr[low];
        return;
    }
    int mid = (low + high) / 2;
    build(2 * idx + 1, low, mid);
    build(2 * idx + 2, mid + 1, high);
    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
}

void applyLazy(int idx, int low, int high) {
    if (lazy[idx] != 0) {
        seg[idx] += (high - low + 1) * lazy[idx]; // update sum
        if (low != high) { // propagate to children
            lazy[2 * idx + 1] += lazy[idx];
            lazy[2 * idx + 2] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int idx, int low, int high, int start, int end, long long val) {
    applyLazy(idx, low, high);

    if (high < start || low > end) return; // no overlap

    if (low >= start && high <= end) { // complete overlap
        seg[idx] += (high - low + 1) * val;
        if (low != high) {
            lazy[2 * idx + 1] += val;
            lazy[2 * idx + 2] += val;
        }
        return;
    }

    int mid = (low + high) / 2;
    update(2 * idx + 1, low, mid, start, end, val);
    update(2 * idx + 2, mid + 1, high, start, end, val);
    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
}

long long query(int idx, int low, int high, int start, int end) {
    applyLazy(idx, low, high);

    if (high < start || low > end) return 0; // no overlap

    if (low >= start && high <= end) return seg[idx]; // complete overlap

    int mid = (low + high) / 2;
    return query(2 * idx + 1, low, mid, start, end)
         + query(2 * idx + 2, mid + 1, high, start, end);
}

int main() {
    int n = 6;
    int arrInit[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < n; i++) arr[i] = arrInit[i];

    build(0, 0, n - 1);

    update(0, 0, n - 1, 1, 3, 10); // add 10 to [1, 3]
    cout << query(0, 0, n - 1, 1, 3) << "\n"; // sum of [1, 3]
    cout << query(0, 0, n - 1, 0, 5) << "\n"; // sum of all
}
