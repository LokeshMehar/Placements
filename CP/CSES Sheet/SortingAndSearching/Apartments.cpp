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
    int n, m , k;
    cin >> n >> m >> k;
    

    vector<int> desired(n);
    vector<int> available(m);
    for(int i= 0;i<n;i++)
    {
        cin >> desired[i];
    }

    for(int i= 0;i<m;i++)
    {
        cin >> available[i];
    }

    sort(desired.begin(),desired.end());
    sort(available.begin(),available.end());

    int i = 0 , j= 0;

    int ans = 0;
    while(i < n && j < m)
    {
        ll lowDesire = desired[i] - k;
        ll highDesire = desired[i] + k;

        ll at = available[j];
        if(at >= lowDesire && at <= highDesire)
        {
            ans++;
            i++;
            j++;
        }
        else if(at  < lowDesire)
        {
            j++;
        }
        else if(at > highDesire)
        {
            i++;
        }
    }

    cout << ans ;

    
    return 0;
}