#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;

    ordered_set<int> st;
    for(int i = 1; i <= n; i++) {
        st.insert(i);
    }
    
    int pos = 0;
    
    while(!st.empty())
    {
        int remaining = st.size();
        pos = (pos + k) % remaining;
        
        // O(log n) access by index!
        auto it = st.find_by_order(pos);
        
        cout << *it << " ";
        st.erase(it);
        
        // Adjust position for next iteration
        if(pos >= st.size() && !st.empty()) {
            pos = 0;
        }
    }
    
    return 0;
}