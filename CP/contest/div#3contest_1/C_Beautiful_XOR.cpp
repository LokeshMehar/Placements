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
    int t;
    cin >> t ;

    while(t--)
    {
        int a,b;
        cin >> a >> b;
        int aCopy = a;
        int maxB = 0;
        int bit = 0;
        while(aCopy)
        {
            maxB += pow(2,bit);
            bit++;
            aCopy = aCopy>>1;
        }
        if(maxB < b)
        {
            cout << -1 << endl;
            continue;
        }
        else
        {
            if(a==b)
            {
                cout << 0 <<ln;
                continue;
            }
            int count = 0;
            vector<int> ans;
            count = 1;
            ans.push_back(0);
            for(int i=0;i<31;i++)
            {
                int bit = 1;
                bit = bit<<i;
                if(((bit&a) == 0) && (bit&b))
                {
                    count++;
                    ans.push_back(bit);
                }
            }
            cout << count << ln;
            for(int e : ans)cout << e << " ";
            cout << ln;
        }
    }
    return 0;
}