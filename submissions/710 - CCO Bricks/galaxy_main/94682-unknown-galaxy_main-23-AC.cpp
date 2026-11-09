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

struct DSU {

    vi sz;
    vi rep;

    DSU (int n) {
        sz.resize(n);
        rep.resize(n);

        for(int i=0;i<n;i++) {
            rep[i]=i;
            sz[i]=1;
        }
    }

    int find(int v) {
        if(rep[v]==v)
            return v;

        rep[v]=find(rep[v]);
        return rep[v];
    }

    void unite(int u, int v) {
        int pu=find(u);
        int pv=find(v);
        if(sz[pu]<sz[pv])
            swap(pu,pv);

        rep[pv]=pu;
        sz[pu]+=sz[pv];
    }
};

void solve() {
    
    int n,m,q;
    cin>>n>>m>>q;

    vector<string> g (n);
    for(int i=0;i<n;i++) 
        cin>>g[i];
    
    vector<vi> adj (n*m);
    vector<pii> disp {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    DSU dsu (n*m);
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            //check 4 adjacents
    
            for(auto [dy,dx]:disp) {
                int ni=i+dy;
                int nj=j+dx;

                if(ni<0||nj<0||ni>=n||nj>=m)
                    continue;

                if(!(g[i][j]=='R'&&g[ni][nj]=='B')&&!(g[i][j]=='B'&&g[ni][nj]=='R')) {
                    dsu.unite(i*m+j, ni*m+nj);
                }
            }
        }
    }


    for(int i=0;i<q;i++) {
        int stx, sty, enx, eny;
        cin>>sty>>stx>>eny>>enx;

        int st=sty*m+stx;
        int en=eny*m+enx;

        if(dsu.find(st)==dsu.find(en)) {
            cout<<"YES\n";
        }else {
            cout<<"NO\n";
        }

    }
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