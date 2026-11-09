#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define int long long
#define double long double
#define vi vector<int>
#define vvi vector<vector<int>>
#define pii pair<int,int>
#define sz(s) s.size()
#define all(x) x.begin(), x.end()
#define pb push_back
#define fi first
#define se second

#define dbg(x) cerr << #x << " = " << x << '\n'

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    
    int n,m,k;
    cin>>n>>m>>k; //m semesters, k courses at most taken per semester

    //each course can be described as:
    //[how many children, course id]
    //we start by having a few

    vector<vi> adj (n+1);
    vi has_par (n+1, 0);
    vi chain (n+1, 0);

    priority_queue<pii> Q;
    for(int i=1;i<=n;i++) {
        int p;
        cin>>p;
        if(p) {
            adj[p].pb(i);
            has_par[i]=1;
        }
    }

    auto dfs=[&](int v, auto&&dfs) -> void {
        for(int to:adj[v]) {
            dfs(to, dfs);
            chain[v]=max(chain[v], chain[to]+1);
        }
        chain[v]=max(chain[v],1ll);
    };

    for(int i=1;i<=n;i++) {
        if(!has_par[i]) {
            dfs(i, dfs);
            Q.push({chain[i], i});

        }
    }

    int ans=0;
    //each semester, we take max of k
    for(int i=0;i<m;i++) {
        int take=0;
        vector<pii> unlock;
        
        while(!Q.empty()) {
            auto [chf, v]=Q.top();
            Q.pop();

            ans++;
            take++;

            for(int to:adj[v]) {
                unlock.pb({chain[to],to});
            }
            if(take==k)
                break;
        }

        for(auto [a,b]:unlock)
            Q.push({a,b});

    }
    cout<<ans<<"\n";
}

signed main () {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t=1;
    cin>>t;

    while(t>0) {
        solve();
        t--;
    }
}