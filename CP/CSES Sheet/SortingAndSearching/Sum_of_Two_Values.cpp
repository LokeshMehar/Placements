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
    int n ,k;
    cin >> n >> k;
    

    vector<pair<int,int>> nums(n);
    for(int i= 0;i<n;i++)
    {
        cin >> nums[i].first;
        nums[i].second = i;
    }

    sort(nums.begin(),nums.end());

    int left = 0 , right= nums.size() - 1;



    pair<int,int> ans = {-1,-1};

    while(left < right)
    {
        ll r = nums[right].first,l = nums[left].first;
        ll sum = l + r;
        if(sum == k)
        {
            ans.first = nums[left].second;
            ans.second = nums[right].second;
            break;
        }
        else if(sum < k)
        {
            left++;
        }
        else{
            right--;
        }

    }

    if(ans.first == -1)
    {
        cout << "IMPOSSIBLE";
    }
    else
    {
        cout << ans.first+1 << " " << ans.second+1;
    }
    

    

    
    return 0;
}