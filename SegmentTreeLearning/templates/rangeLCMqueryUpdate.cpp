#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
long long arr[N];
long long seg[4 * N];

long long gcdFunc(long long a, long long b) {
    return b == 0 ? a : gcdFunc(b, a % b);
}

long long lcmFunc(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return a / gcdFunc(a, b) * b; // safe from overflow if a,b <= 1e9
}

void build(int idx, int low, int high) {
    if (low == high) {
        seg[idx] = arr[low];
        return;
    }
    int mid = (low + high) / 2;
    build(2 * idx + 1, low, mid);
    build(2 * idx + 2, mid + 1, high);
    seg[idx] = lcmFunc(seg[2 * idx + 1], seg[2 * idx + 2]);
}

long long query(int idx, int low, int high, int l, int r) {
    if (r < low || high < l) return 1; // lcm(x,1) = x
    if (l <= low && high <= r) return seg[idx];
    int mid = (low + high) / 2;
    long long leftLCM = query(2 * idx + 1, low, mid, l, r);
    long long rightLCM = query(2 * idx + 2, mid + 1, high, l, r);
    return lcmFunc(leftLCM, rightLCM);
}

void update(int idx, int low, int high, int targetIdx, long long val) {
    if (low == high) {
        seg[idx] = val;
        arr[low] = val;
        return;
    }
    int mid = (low + high) / 2;
    if (targetIdx <= mid)
        update(2 * idx + 1, low, mid, targetIdx, val);
    else
        update(2 * idx + 2, mid + 1, high, targetIdx, val);
    seg[idx] = lcmFunc(seg[2 * idx + 1], seg[2 * idx + 2]);
}

int main() {
    int n = 5;
    long long input[] = {2, 7, 3, 9, 4};
    for (int i = 0; i < n; i++) arr[i] = input[i];

    build(0, 0, n - 1);

    cout << query(0, 0, n - 1, 1, 3) << "\n"; // LCM from index 1 to 3
    update(0, 0, n - 1, 2, 6);                 // arr[2] = 6
    cout << query(0, 0, n - 1, 1, 3) << "\n";
}
