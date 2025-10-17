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
    cin >> n;
    vector<int> nums(n);
    for(int i=0;i<n;i++)
    {
        cin >> nums[i];
    }
    int left  = 0;
    int right = 0;
    set<int> mp;  
    ll ret  = 0;
    while(right  < n)
    {
        while(mp.find(nums[right]) != mp.end())
        {
            mp.erase(nums[left]);
            left++;
        }
        ret += right- left + 1LL;
        mp.insert(nums[right]);
        right++;
    }

    cout << ret ;

    

    

    
    return 0;
}