
#include <bits/stdc++.h>
using namespace std;
#define ln '\n'
typedef long long ll;
const int MOD = 1e9 + 7;


struct range
{
    int l;int r;int idx;
    bool operator < (const range& other)
    {
        if(l==other.l)return r > other.r;
        return l<other.l;
    }
};
int main()
{
    ios_base:: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n ;
    cin >> n ;

    vector<range> ranges(n);
    for(int i=0;i<n;i++)
    {
        int start ,end;
        cin >>start >> end;
        ranges[i].l = start;
        ranges[i].r = end;
        ranges[i].idx = i;
    }

    sort(ranges.begin(),ranges.end());
    vector<bool> contained(n,false),contains(n,false);
    int mx = 0;
    for(int i=0;i<n;i++)
    {
        if(mx >= ranges[i].r)contained[ranges[i].idx]=true;
        mx= max(mx,ranges[i].r);
    }
    cout << ln;
    int mn = 1e9 + 3;
    for(int i=n-1;i>=0;i--)
    {
        if(mn<=ranges[i].r)contains[ranges[i].idx]=true;
        mn = min(mn,ranges[i].r);
    }
    for(int  i=0;i<n;i++)
    {
        cout << contains[i] << " ";
    }
    cout << ln;
    for(int  i=0;i<n;i++)
    {
        cout << contained[i] << " ";
    }
    return 0;
}