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
    int n ,  m;
    cin >> n >>m;
    

    vector<int> nums(n+1);
    vector<int>  pos(n+1);
    for(int i= 1;i<=n;i++)
    {
        cin >> nums[i];
        pos[nums[i]] = i;
    }

    ll ans=1;
    for(int i=1;i<n;i++)
    {
        ans += pos[i] > pos[i+1];
    }

    set<pair<int,int>> updated;
    for(int i =0 ;i<m;i++)
    {
        int a,b;
        cin >> a >> b;
        if(nums[a] + 1 <= n) updated.insert({nums[a],nums[a]+1});
        if(nums[a] - 1 >= 1) updated.insert({nums[a]-1,nums[a]});
        if(nums[b] + 1 <= n) updated.insert({nums[b],nums[b]+1});
        if(nums[b] - 1 >= 1) updated.insert({nums[b]-1,nums[b]});

        for(pair<int,int> swapped : updated)
            ans -= pos[swapped.first] > pos[swapped.second];
        
        swap(nums[a],nums[b]);
        pos[nums[a]] = a;
        pos[nums[b]] = b;

        for(pair<int,int> swapped : updated)
            ans += pos[swapped.first] > pos[swapped.second];

        cout << ans << ln;
        updated.clear();

    }


    
    // cout << ans;
    

    

    
    return 0;
}