//my code

// #include <bits/stdc++.h>
// using namespace std;
// #define ln '\n'
// typedef long long ll;
// const int MOD = 1e9 + 7;



// int main()
// {
//     ios_base:: sync_with_stdio(false);
//     cin.tie(NULL);
//     cout.tie(NULL);
//     int n ;
//     cin >> n ;

//     set<int> st;
//     for(int i=1;i<=n;i++)st.insert(i);
//     auto it = st.begin();
//     while(st.size() > 1)
//     {
//         auto next = it;
//         next++;
//         if(next == st.end())
//         {
//             next = st.begin();
//         }

//         cout << *next << " ";

//         auto temp = next;
//         temp++;

//         if(temp == st.end())
//         {
//             temp = st.begin();
//         }

//         st.erase(next);
//         it = temp;

//     }

//     cout << *st.begin();

//     st.clear();
    

    

    

    
//     return 0;
// }

//github junk code hahahahahhaaa(i learned to much from  this too <3)
#include <bits/stdc++.h>
#define ll long long int
using namespace std;

void solve(ll N)
{
    queue<ll> q;
    // Push all the children to the queue
    for (int i = 1; i <= N; i++)
        q.push(i);

    // Set the flag to false, so that the first child does
    // not get removed
    bool flag = false;

    while (!q.empty()) {
        int ele = q.front();
        q.pop();
        // If we have to remove the element, print it
        if (flag) {
            cout << ele << " ";
        }
        // If we don't have to remove the element, push it
        // back to the queue
        else {
            q.push(ele);
        }
        // Toggle the value of flag so that only the
        // alternate elements get removed
        flag = !flag;
    }
}

int main()
{
    ll N = 7;
    solve(N);
}