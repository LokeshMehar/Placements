#include <bits/stdc++.h>
using namespace std;
#define ln '\n'
typedef long long ll;
const int MOD = 1e9 + 7;



int main()
{
    ios_base:: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n , x ;
    cin >>x >> n ;

    set<int> st;
    st.insert(0);
    st.insert(x);

    multiset<int> mset;

    mset.insert(x);

    for(int i=0;i<n;i++)
    {
        int p ;
        cin >> p;

        auto right = st.lower_bound(p);
        auto left = prev(right);

        int nextEnd = *right;
        int prevStart = *left;

        mset.erase(mset.find(nextEnd - prevStart));
        st.insert(p);
        mset.insert(nextEnd - p);
        mset.insert(p-prevStart);

        cout  << *mset.rbegin() << " ";


    }
    

    

    

    
    return 0;
}