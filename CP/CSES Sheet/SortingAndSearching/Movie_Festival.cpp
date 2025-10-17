#include <bits/stdc++.h>
using namespace std;
#define ln '\n'
typedef long long ll;
const int MOD = 1e9 + 7;

bool cmp(pair<int,int>& a,pair<int,int>& b)
{
    return a.second < b.second;
}

int main()
{
    ios_base:: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n ;
    
    vector<pair<int,int>> vc(n);
    for(int i= 0;i<n;i++)
    {
        cin >> vc[i].first >> vc[i].second;
    }
    sort(vc.begin(),vc.end(),cmp);


    int ans = 0 , last = -1;

    for(int i=0;i<n;i++)
    {
        if(last <= vc[i].first)
        {
            ans++;
            last =vc[i].second;
        }
    }
    
    cout << ans ;
    
    return 0;
}