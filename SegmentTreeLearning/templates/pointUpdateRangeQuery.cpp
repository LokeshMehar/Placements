#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int arr[N];
int seg[4 * N];

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

void update(int idx, int low, int high, int targetIdx, int val) {
    if (low == high) {
        seg[idx] = val;
        return;
    }
    int mid = (low + high) / 2;
    if (targetIdx <= mid) update(2 * idx + 1, low, mid, targetIdx, val);
    else update(2 * idx + 2, mid + 1, high, targetIdx, val);
    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
}

int query(int idx, int low, int high, int start, int end) {
    if (start > high || end < low) return 0; // no overlap
    if (low >= start && high <= end) return seg[idx]; // total overlap
    int mid = (low + high) / 2;
    int left = query(2 * idx + 1, low, mid, start, end);
    int right = query(2 * idx + 2, mid + 1, high, start, end);
    return left + right;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];

    build(0, 0, n - 1);

    // Example usage
    cout << query(0, 0, n - 1, 1, 3) << "\n"; // sum from index 1 to 3
    update(0, 0, n - 1, 2, 10); // set arr[2] = 10
    cout << query(0, 0, n - 1, 1, 3) << "\n";
}
