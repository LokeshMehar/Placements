#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int arr[N];
int seg[4 * N];

int gcdFunc(int a, int b) {
    return b == 0 ? a : gcdFunc(b, a % b);
}


void build(int idx, int low, int high) {
    if (low == high) {
        seg[idx] = arr[low];
        return;
    }
    int mid = (low + high) / 2;
    build(2 * idx + 1, low, mid);
    build(2 * idx + 2, mid + 1, high);
    seg[idx] = gcdFunc(seg[2 * idx + 1], seg[2 * idx + 2]);
}

int query(int idx, int low, int high, int l, int r) {
    if (r < low || high < l) return 0; // gcd(x,0)=x
    if (l <= low && high <= r) return seg[idx];
    int mid = (low + high) / 2;
    int leftGCD = query(2 * idx + 1, low, mid, l, r);
    int rightGCD = query(2 * idx + 2, mid + 1, high, l, r);
    return gcdFunc(leftGCD, rightGCD);
}

void update(int idx, int low, int high, int targetIdx, int val) {
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
    seg[idx] = gcdFunc(seg[2 * idx + 1], seg[2 * idx + 2]);
}

int main() {
    int n = 5;
    int input[] = {2, 4, 6, 8, 16};
    for (int i = 0; i < n; i++) arr[i] = input[i];

    build(0, 0, n - 1);

    cout << query(0, 0, n - 1, 1, 3) << "\n"; // GCD from index 1 to 3
    update(0, 0, n - 1, 2, 10);               // arr[2] = 10
    cout << query(0, 0, n - 1, 1, 3) << "\n";
}
