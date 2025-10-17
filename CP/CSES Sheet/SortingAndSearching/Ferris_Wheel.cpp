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
    int n,  k;
    cin >> n >> k;
    

    vector<int> weight(n);
    for(int i= 0;i<n;i++)
    {
        cin >> weight[i];
    }

    sort(weight.begin(),weight.end());

    int left = 0 , right= weight.size() - 1;



    int ans = 0;

    while(left <= right)
    {
        ll r = weight[right],l = weight[left];
        if(l+r <= k)
        {
            left ++;
            right--;
        }
        else{
            right--;
        }
        ans ++;
    }
    

    cout << ans ;

    
    return 0;
}