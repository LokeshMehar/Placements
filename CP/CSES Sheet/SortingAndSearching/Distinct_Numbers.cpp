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
    int n;
    cin >> n;
    set<int>  st;
    for(int i=0;i<n;i++)
    {
        int at;
        cin >> at;
        st.insert(at);
    }
    cout << st.size();

    
    return 0;
}