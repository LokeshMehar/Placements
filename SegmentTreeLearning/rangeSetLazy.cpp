#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long sum, mn, mx;
};

vector<Node> seg;
vector<long long> lazySetVal; // value to set
vector<bool> lazySetFlag;     // is there a pending set?
vector<long long> arr;
int n;

Node mergeNode(Node a, Node b) {
    return {a.sum + b.sum, min(a.mn, b.mn), max(a.mx, b.mx)};
}

void buildSeg(int idx, int low, int high) {
    if (low == high) {
        seg[idx] = {arr[low], arr[low], arr[low]};
        return;
    }
    int mid = (low + high) / 2;
    buildSeg(idx*2+1, low, mid);
    buildSeg(idx*2+2, mid+1, high);
    seg[idx] = mergeNode(seg[idx*2+1], seg[idx*2+2]);
}

// apply "set to val" on current node
void applySet(int idx, int low, int high, long long val) {
    seg[idx].sum = (high - low + 1) * val;
    seg[idx].mn = val;
    seg[idx].mx = val;
    lazySetVal[idx] = val;
    lazySetFlag[idx] = true;
}

// push lazy assignment to children
void pushDown(int idx, int low, int high) {
    if (lazySetFlag[idx]) {
        int mid = (low + high) / 2;
        applySet(idx*2+1, low, mid, lazySetVal[idx]);
        applySet(idx*2+2, mid+1, high, lazySetVal[idx]);
        lazySetFlag[idx] = false; // cleared after pushing
    }
}

void updateRangeSet(int idx, int low, int high, int start, int end, long long val) {
    if (low > end || high < start) return;
    if (start <= low && high <= end) {
        applySet(idx, low, high, val);
        return;
    }
    pushDown(idx, low, high);
    int mid = (low + high) / 2;
    updateRangeSet(idx*2+1, low, mid, start, end, val);
    updateRangeSet(idx*2+2, mid+1, high, start, end, val);
    seg[idx] = mergeNode(seg[idx*2+1], seg[idx*2+2]);
}

Node queryRange(int idx, int low, int high, int start, int end) {
    if (low > end || high < start) return {0, LLONG_MAX, LLONG_MIN};
    if (start <= low && high <= end) return seg[idx];
    pushDown(idx, low, high);
    int mid = (low + high) / 2;
    Node left = queryRange(idx*2+1, low, mid, start, end);
    Node right = queryRange(idx*2+2, mid+1, high, start, end);
    return mergeNode(left, right);
}

int main() {
    n = 6;
    arr = {1, 3, 5, 7, 9, 11};
    seg.assign(4*n, {0,0,0});
    lazySetVal.assign(4*n, 0);
    lazySetFlag.assign(4*n, false);
    buildSeg(0, 0, n-1);

    // set range [1,3] to value 5
    updateRangeSet(0, 0, n-1, 1, 3, 5);

    Node res = queryRange(0, 0, n-1, 0, 5);
    cout << "Sum: " << res.sum << " Min: " << res.mn << " Max: " << res.mx << "\n";
}
