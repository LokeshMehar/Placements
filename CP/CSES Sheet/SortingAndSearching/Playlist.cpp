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
    int left = 0,right = 0;
    map<int,int> mp;
    int ans  = 0;
    while(right < n)
    {
        int at = nums[right];
        mp[at]++;
        while(mp[at] > 1)
        {
            mp[nums[left]]--;
            left++;
        }
        ans =max(right - left + 1,ans);
        right++;
    }
    cout << ans;
    

    

    
    return 0;
}