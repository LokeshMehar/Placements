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

    int at  = 2;
    while(at<=n)
    {
        cout << at << " ";
        at+=2; 
    }
    at  = 1;
    while(at<=n)
    {
        cout << at << " ";
        at+=2; 
    }
    

    

    

    
    return 0;
}