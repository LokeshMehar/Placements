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
    int n ;
    cin >> n ;
    

    vector<int> nums(n);
    vector<int>  pos(n);
    for(int i= 0;i<n;i++)
    {
        cin >> nums[i];
        nums[i]--;
        pos[nums[i]] = i;
    }
    ll ans=1;
    for(int i=1;i<n;i++)
    {
        ans += pos[i] < pos[i-1];
    }
    cout << ans;
    

    

    
    return 0;
}