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
//     int n,  k;
//     cin >> n ;
    

//     map<int,int> mp;
//     for(int i= 0;i<n;i++)
//     {
//         int arrival , departure;
//         cin >> arrival >> departure;
//         mp[arrival]++;
//         mp[departure]--;
//     }



//     int ans = 0 , ac = 0;

//     for (auto it = mp.begin(); it != mp.end(); ++it)
// {
//     int key = it->first;
//     int val = it->second;
//     ac += val;
//     ans = max(ans, ac);
// }
    

//     cout << ans ;

    
//     return 0;
// }







int solve(int n, int k, vector<int> special, vector<int> from, vector<int> to) {
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u = from[i], v = to[i];
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    auto bfs = [&](int start) -> vector<int> {
        vector<int> dist(n + 1, -1);
        queue<int> q;
        q.push(start);
        dist[start] = 0;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int nxt : adj[curr]) {
                if (dist[nxt] == -1) {
                    dist[nxt] = dist[curr] + 1;
                    q.push(nxt);
                }
            }
        }
        return dist;
    };

    vector<int> distA = bfs(1);
    vector<int> distB = bfs(n);
    vector<int> sp = special;

    sort(sp.begin(), sp.end(), [&](int x, int y) {
        return (long long)distA[x] - distB[x] < (long long)distA[y] - distB[y];
    });

    int bestA = -1000000007, bestB = -1000000007;
    for (int node : sp) {
        if (bestA > -1000000007)
            bestB = max(bestB, bestA + distB[node]);
        bestA = max(bestA, distA[node]);
    }

    int ans = min(distA[n], bestB + 1);
    return ans;
}




















long long solve(int n, long long k, vector<long long> a) {
    sort(a.begin(), a.end());
    int left = 0, right = n-1;
    ll c=1, d=1;
    
    while(k>0 && left<right && a[left] < a[right])
    {
        // ADD THESE TWO WHILE LOOPS HERE (before computing u and v):
        while(left<right && a[left] == a[left+1]) {
            left++;
            c++;
        }
        while(left < right && a[right] == a[right-1]) {
            right--;
            d++;
        }
        
        if(left >= right) break;  // ADD THIS CHECK
        
        ll u = a[left+1] - a[left];
        ll v = a[right] - a[right-1];
        ll s = c*u;
        ll t = d*v;
        
        if(s<=t)
        {
            if(k>=s)
            {
                k-=s;
                left++;
                c++;
            }
            else
            {
                ll x = k/c, y= k/d;
                if(x>-y) a[left]+=x;
                else a[right]-=y;
                break;
            }
        }
        else
        {
            if(k>= t)
            {
                k-= t;
                right--;
                d++;
            }
            else
            {
                ll x = k/c, y= k/d;
                if(x>-y) a[left] += x;
                else a[right] -= y;
                break;
            }
        }
    }
    
    return a[right] - a[left];
}

























long long solve(int n, long long k, vector<long long> a) {
    sort(a.begin(), a.end());
    int left = 0, right = n - 1;
    long long countL = 1, countR = 1;

    while (left < right && a[left] < a[right] && k > 0) {
        while (left < right && a[left] == a[left + 1]) { 
            left++; 
            countL++; 
        }
        while (left < right && a[right] == a[right - 1]) { 
            right--; 
            countR++; 
        }
        if (left >= right) break;

        long long diffLeft = a[left + 1] - a[left];
        long long diffRight = a[right] - a[right - 1];
        long long needLeft = countL * diffLeft;
        long long needRight = countR * diffRight;

        if (needLeft <= needRight) {
            if (k >= needLeft) {
                k -= needLeft;
                left++;
                countL++;
            } else {
                long long addVal = k / countL;
                a[left] += addVal;
                break;
            }
        } else {
            if (k >= needRight) {
                k -= needRight;
                right--;
                countR++;
            } else {
                long long subVal = k / countR;
                a[right] -= subVal;
                break;
            }
        }
    }

    return a[right] - a[left];
}


























long long solve(int n,long long k,vector<long long> a){
    sort(a.begin(),a.end());
    if(n<=1) return 0;
    int l=0,r=n-1;
    long long L=a[l],R=a[r],x=1,y=1;
    while(l<r&&k>0&&L<R){
        while(l+1<=r&&a[l+1]<=L){l++;x++;}
        while(r-1>=l&&a[r-1]>=R){r--;y++;}
        if(l>=r||L>=R) break;
        long long nl=(l+1<=r?min(a[l+1],R):R);
        long long nr=(r-1>=l?max(a[r-1],L):L);
        long long dl=nl-L,dr=R-nr;
        if(dl<=0&&dr<=0) break;
        long long tl=dl>0?dl*x:(long long)4e18;
        long long tr=dr>0?dr*y:(long long)4e18;
        long long t=min({tl,tr,k});
        if(t==0) break;
        L+=t/x;
        R-=t/y;
        k-=t;
        if(L>=R) return 0;
    }
    while(l+1<=r&&a[l+1]<=L){l++;x++;}
    while(r-1>=l&&a[r-1]>=R){r--;y++;}
    long long d=R-L;
    if(d<=0) return 0;
    long long z=max(k/x,k/y);
    if(z>d) z=d;
    return d-z;
}