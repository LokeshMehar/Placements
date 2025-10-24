#include <iostream>
#include <vector>
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
        int n ;
        cin >> n;

        int mx = 0;
        vector<int> vc;
        for(int i=1;i<=n;i++)
        {
            char at ;
            cin >> at;
            if(at=='0')
            {
                mx++;
                vc.push_back(i);
            }
        }
        cout << mx << ln;
        for(int e : vc)cout << e << " ";
        cout << ln;
    }
    return 0;
}