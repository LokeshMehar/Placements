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
    ll sum = 0;
    ll ans = LLONG_MIN;
    int right=0;
    while(right <n)
    {
        sum+= nums[right];
        ans=(max(ans,sum));

        if(sum< 0)
        {
            sum = 0;
        }
        right++;

    }
    cout << ans;
    

    

    
    return 0;
}