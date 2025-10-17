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

    vector<pair<ll,ll>> nums(n);

    for(int i=0;i<n;i++)
    {
        ll duration,deadline;
        cin >> duration >> deadline;
        nums[i].first = duration;
        nums[i].second  =  deadline;
    }
    ll time = 0;
    ll reward = 0;
    sort(nums.begin(),nums.end());
    for(int i=0;i<n;i++)
    {
        time += nums[i].first;
        reward += (nums[i].second - time);
    }

    cout << reward;


    

    

    

    
    return 0;
}