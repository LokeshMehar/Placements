#include <bits/stdc++.h>
using namespace std;

/*
  Problem: Slice Master
  Given a string S, slice it into parts such that each character
  appears in at most one part. The score for each part = (length)^2.
  Return the minimum possible total score.
*/

long long solveG(string S) {
    vector<int> first(26, -1);
    vector<int> last(26, -1);
    int n = S.length();

    if (n == 0) return 0;

    // Step 1: Record first and last occurrence of each character
    for (int i = 0; i < n; ++i) {
        int char_idx = S[i] - 'a';
        if (first[char_idx] == -1)
            first[char_idx] = i;
        last[char_idx] = i;
    }

    // Step 2: Traverse and find partition points
    long long lo = 0, start = 0, ret = 0;

    for (int i = 0; i < n; i++) {
        lo = max(lo, (long long)last[S[i] - 'a']);
        if (lo == i) {
            long long len = i - start + 1;
            ret += (len * len);
            start = i + 1; // start next partition
        }
    }

    return ret;
}

int main() {
    string S;
    cin >> S;  // input string

    cout << solveG(S) << endl;  // print minimum possible score
    return 0;
}
