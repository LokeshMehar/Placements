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
    cin >> n;

    vector<int> towers;

    for(int i=0;i<n;i++)
    {
        int toAdd;
        cin >> toAdd;

        int low = 0;
        int high =  towers.size() - 1;
        int place =  towers.size();

        while(low <=  high)
        {
            int mid  = low  + ((high - low)>> 1);
            if(towers[mid] > toAdd)
            {
                place = mid;
                high = mid -1;
            }
            else
            {
                low =  mid + 1;
            }
        }

        if(place ==  towers.size())
        {
            towers.push_back(toAdd);
        }
        else{
            towers[place]=toAdd;
        }

    }

    cout << towers.size();

    

    

    
    return 0;
}