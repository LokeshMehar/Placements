#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long sum, mn, mx;
};

vector<Node> seg;
vector<long long> lazy;
vector<long long> arr;
int n;

Node mergeNode(Node a, Node b) {
    return {a.sum + b.sum, min(a.mn, b.mn), max(a.mx, b.mx)};
}

void buildSeg(int idx, int low, int high) 
{
    if (low == high) 
    {
        seg[idx] = {arr[low], arr[low], arr[low]};
        return;
    }
    int mid = (low + high) / 2;
    buildSeg(idx*2+1, low, mid);
    buildSeg(idx*2+2, mid+1, high);
    seg[idx] = mergeNode(seg[idx*2+1], seg[idx*2+2]);
}

void applyLazy(int idx, int low, int high, long long val) 
{
    seg[idx].sum += (high - low + 1) * val;
    seg[idx].mn += val;
    seg[idx].mx += val;
    lazy[idx] += val;
}

void updateRange(int idx, int low, int high, int start, int end, long long val) 
{
    if (lazy[idx] != 0) 
    { // Apply pending lazy updates
        applyLazy(idx, low, high, lazy[idx]);
        if (low != high) {
            lazy[idx*2+1] += lazy[idx];
            lazy[idx*2+2] += lazy[idx];
        }
        lazy[idx] = 0;
    }
    if (low > end || high < start) return;
    if (start <= low && high <= end) {
        applyLazy(idx, low, high, val);
        if (low != high) {
            lazy[idx*2+1] += val;
            lazy[idx*2+2] += val;
        }
        return;
    }
    int mid = (low + high) / 2;
    updateRange(idx*2+1, low, mid, start, end, val);
    updateRange(idx*2+2, mid+1, high, start, end, val);
    seg[idx] = mergeNode(seg[idx*2+1], seg[idx*2+2]);
}

Node queryRange(int idx, int low, int high, int start, int end) 
{
    if (lazy[idx] != 0) { // Apply pending lazy updates
        applyLazy(idx, low, high, lazy[idx]);
        if (low != high) 
        {
            lazy[idx*2+1] += lazy[idx];
            lazy[idx*2+2] += lazy[idx];
        }
        lazy[idx] = 0;
    }
    if (low > end || high < start) return {0, LLONG_MAX, LLONG_MIN};
    if (start <= low && high <= end) return seg[idx];
    int mid = (low + high) / 2;
    Node left = queryRange(idx*2+1, low, mid, start, end);
    Node right = queryRange(idx*2+2, mid+1, high, start, end);
    return mergeNode(left, right);
}

int main() {
    n = 6;
    arr = {1, 3, 5, 7, 9, 11};
    seg.assign(4*n, {0,0,0});
    lazy.assign(4*n, 0);
    buildSeg(0, 0, n-1);

    updateRange(0, 0, n-1, 1, 3, 5); // add +5 to index 1..3
    Node res = queryRange(0, 0, n-1, 0, 5);
    cout << "Sum: " << res.sum << " Min: " << res.mn << " Max: " << res.mx << "\n";
}
