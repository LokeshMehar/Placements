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
    for(int i= 0;i<n;i++)
    {
        cin >> nums[i];
    }
    sort(nums.begin(),nums.end());
    ll x =  nums[n/2];
    ll ans=0;
    for(int e : nums)
    {
        ans  += abs(x-e);
    }
    cout << ans;
    

    

    
    return 0;
}