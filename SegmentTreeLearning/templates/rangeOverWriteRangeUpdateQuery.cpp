#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
long long seg[4 * N];
bool setLazy[4 * N];  // whether there's a pending set
long long setVal[4 * N]; // value to set
long long addLazy[4 * N]; // pending add if no set

void build(int idx, int low, int high, vector<long long> &arr) {
    if (low == high) {
        seg[idx] = arr[low];
        return;
    }
    int mid = (low + high) / 2;
    build(2 * idx + 1, low, mid, arr);
    build(2 * idx + 2, mid + 1, high, arr);
    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
}

void applySet(int idx, int low, int high, long long val) {
    seg[idx] = (high - low + 1) * val;
    setLazy[idx] = true;
    setVal[idx] = val;
    addLazy[idx] = 0; // clear pending add
}

void applyAdd(int idx, int low, int high, long long val) {
    if (setLazy[idx]) {
        setVal[idx] += val;
        seg[idx] = (high - low + 1) * setVal[idx];
    } else {
        seg[idx] += (high - low + 1) * val;
        addLazy[idx] += val;
    }
}

void pushDown(int idx, int low, int high) {
    int mid = (low + high) / 2;
    if (setLazy[idx]) {
        applySet(2 * idx + 1, low, mid, setVal[idx]);
        applySet(2 * idx + 2, mid + 1, high, setVal[idx]);
        setLazy[idx] = false;
    }
    if (addLazy[idx] != 0) {
        applyAdd(2 * idx + 1, low, mid, addLazy[idx]);
        applyAdd(2 * idx + 2, mid + 1, high, addLazy[idx]);
        addLazy[idx] = 0;
    }
}

void rangeSet(int idx, int low, int high, int start, int end, long long val) {
    if (start > high || end < low) return;
    if (start <= low && high <= end) {
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
    if (start > high || end < low) return;
    if (start <= low && high <= end) {
        applyAdd(idx, low, high, val);
        return;
    }
    pushDown(idx, low, high);
    int mid = (low + high) / 2;
    rangeAdd(2 * idx + 1, low, mid, start, end, val);
    rangeAdd(2 * idx + 2, mid + 1, high, start, end, val);
    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
}

long long rangeQuery(int idx, int low, int high, int start, int end) {
    if (start > high || end < low) return 0;
    if (start <= low && high <= end) return seg[idx];
    pushDown(idx, low, high);
    int mid = (low + high) / 2;
    return rangeQuery(2 * idx + 1, low, mid, start, end) +
           rangeQuery(2 * idx + 2, mid + 1, high, start, end);
}

int main() {
    int n = 6;
    vector<long long> arr = {1, 2, 3, 4, 5, 6};
    build(0, 0, n - 1, arr);

    rangeAdd(0, 0, n - 1, 1, 3, 5);  // add 5 to indices 1..3
    rangeSet(0, 0, n - 1, 2, 4, 10); // set indices 2..4 to 10
    cout << rangeQuery(0, 0, n - 1, 0, 5) << "\n"; // total sum
}
