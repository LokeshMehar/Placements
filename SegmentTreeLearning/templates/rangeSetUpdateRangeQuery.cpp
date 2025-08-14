#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
long long seg[4 * N], lazyAdd[4 * N], lazySet[4 * N];
bool hasSet[4 * N]; // track if lazySet is active
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

void applySet(int idx, int low, int high, long long val) {
    seg[idx] = (high - low + 1) * val;
    lazySet[idx] = val;
    hasSet[idx] = true;
    lazyAdd[idx] = 0; // reset add because set overrides it
}

void applyAdd(int idx, int low, int high, long long val) {
    seg[idx] += (high - low + 1) * val;
    if (hasSet[idx]) {
        lazySet[idx] += val; // adjust set value if already set
    } else {
        lazyAdd[idx] += val;
    }
}

void pushDown(int idx, int low, int high) {
    if (low == high) return;
    int mid = (low + high) / 2;

    if (hasSet[idx]) {
        applySet(2 * idx + 1, low, mid, lazySet[idx]);
        applySet(2 * idx + 2, mid + 1, high, lazySet[idx]);
        hasSet[idx] = false;
    }
    if (lazyAdd[idx] != 0) {
        applyAdd(2 * idx + 1, low, mid, lazyAdd[idx]);
        applyAdd(2 * idx + 2, mid + 1, high, lazyAdd[idx]);
        lazyAdd[idx] = 0;
    }
}

void rangeSet(int idx, int low, int high, int start, int end, long long val) {
    if (high < start || low > end) return;
    if (low >= start && high <= end) {
        applySet(idx, low, high, val);
        return;
    }
    pushDown(idx, low, high);
    int mid = (low + high) / 2;
    rangeSet(2 * idx + 1, low, mid, start, end, val);
    rangeSet(2 * idx + 2, mid + 1, high, start, end, val);
    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
}

void rangeAdd(int idx, int low, int high, int start, int end, long long val) {
    if (high < start || low > end) return;
    if (low >= start && high <= end) {
        applyAdd(idx, low, high, val);
        return;
    }
    pushDown(idx, low, high);
    int mid = (low + high) / 2;
    rangeAdd(2 * idx + 1, low, mid, start, end, val);
    rangeAdd(2 * idx + 2, mid + 1, high, start, end, val);
    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
}

long long query(int idx, int low, int high, int start, int end) {
    if (high < start || low > end) return 0;
    if (low >= start && high <= end) return seg[idx];
    pushDown(idx, low, high);
    int mid = (low + high) / 2;
    return query(2 * idx + 1, low, mid, start, end)
         + query(2 * idx + 2, mid + 1, high, start, end);
}

int main() {
    int n = 6;
    int arrInit[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < n; i++) arr[i] = arrInit[i];

    build(0, 0, n - 1);

    rangeSet(0, 0, n - 1, 1, 3, 5); // set [1,3] to 5
    cout << query(0, 0, n - 1, 0, 5) << "\n"; // sum all

    rangeAdd(0, 0, n - 1, 2, 4, 2); // add 2 to [2,4]
    cout << query(0, 0, n - 1, 0, 5) << "\n"; // sum all
}
