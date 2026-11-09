#include "bits/extc++.h"

using namespace std;

using ll = long long;

#define sz(x) int(std::size(x))

ll root(ll x){
    ll val=sqrt(x);
    val=max(ll(0),val-10);
    while(val*val<=x) val++;
    val--;
    return val;
}

struct DSU {
    int n;
    vector<int>par,siz,rv;
    DSU(int nv):n(nv),par(n,0),siz(n,1),rv(n,0){
        for(int i = 0; i<n; i++){
            par[i]=i,rv[i]=i;
        }
    }
    int find(int x){
        if(par[x]==x) return x;
        return par[x]=find(par[x]);
    }
    int rrv(int x){
        return rv[find(x)];
    }
    void merge(int a, int b){
        if(a==n || b==n) return;
        a=find(a),b=find(b);
        if(siz[a]<siz[b]) swap(a,b);
        par[b]=a;
        rv[a]=max(rv[a],rv[b]);
    }
};

void solve1(int n, int m, int q, vector<array<int,3>>qu, bool swap){
    vector<vector<ll>>arr(n,vector<ll>(m,0));
    for(int i = 0; i<n; i++){
        vector<pair<int,int>>evnt[m+1];
        vector<array<int,3>>vals;
        for(int j = 0; j<q; j++){
            auto [a,b,p] = qu[j];
            ll val=ll(p)*p-ll(i-a)*(i-a);
            if(val<0) continue;
            int lv = b-root(val), rv = b+root(val);
            evnt[lv].push_back({1,j});
            evnt[rv+1].push_back({-1,j});
            vals.push_back({lv,rv,j});
        }
        reverse(vals.begin(),vals.end());
        auto dist = [&](array<int,3>qv, int x, int y) -> ll {
            auto [r,c,p] = qv;
            return ll(p)*p-ll(x-r)*(x-r)-ll(c-y)*(c-y)+1;
        };

        set<int>valss;
        vector<int>qun(m,-1);
        DSU dsu(m);

        for(auto [l,r,qv]: vals){
            int lv=l;
            while(lv<=r){
                if(qun[lv]==-1){
                    qun[lv]=qv;
                    dsu.merge(lv,lv+1);
                }
                if(lv==m-1) lv=m;
                else lv=dsu.rrv(lv);
            }
        }
        for(int j = 0; j<m; j++){
            if(qun[j]!=-1) arr[i][j]=dist(qu[qun[j]],i,j);
        }
    }
    if(swap){
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                cout<<arr[j][i]<<" ";
            }
            cout<<"\n";
        }
        return;
    }
    for(int i = 0; i<n; i++){
        for(auto u: arr[i]) cout<<u<<" ";
        cout<<"\n";
    }
}

void solve(){
    int n,m,q;
    cin>>n>>m>>q;
    vector<array<int,3>>qu;
    for(int i = 0; i<q; i++){
        int r,c,p;
        cin>>r>>c>>p;
        qu.push_back({r,c,p});
    }
    if(n<=m){
        solve1(n,m,q,qu,0);
    }else{
        swap(n,m);
        for(auto &[a,b,c]: qu){
            swap(a,b);
        }
        solve1(n,m,q,qu,1);
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(ios::failbit);
    int t;
    cin>>t;
    while(t--) solve();
}
