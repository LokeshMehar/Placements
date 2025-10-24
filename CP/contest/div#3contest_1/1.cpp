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
        for(int i=0;i<n;i++)
        {
            int at ;
            cin >> at;
            mx=max(mx,at);
        }
        cout << mx << ln;
    }
    return 0;
}