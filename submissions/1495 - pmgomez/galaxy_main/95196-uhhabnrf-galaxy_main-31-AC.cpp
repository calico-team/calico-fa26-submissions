#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<ll> dxs = {-1,1,0,0};
vector<ll> dys = {0,0,-1,1};
ll N,M;
bool bounds(ll i, ll j){
    return (i>=0 && j>=0 && i < N && j < M);
}
ll comp(ll i, ll j){
    return i*M+j;
}
struct DSU {
    vector<ll> par,sz;
    DSU(ll n){
        par.resize(n);
        sz.resize(n);
        for (ll i=0;i<n;i++){
            par[i]=i;
            sz[i]=1;
        }
    }
    ll find(ll u){
        if (par[u]==u) return u;
        return par[u] = find(par[u]);
    }
    void join(ll u, ll v){
        u = find(u), v = find(v);
        if (u==v) return;
        if (sz[u]>sz[v]){
            swap(u,v);
        }
        sz[v]+=sz[u];
        par[u]=v;
    }
};
void solve(){
    ll Q;cin>>N>>M>>Q;
    vector<string> grid(N);
    for (ll i=0;i<N;i++){
        cin>>grid[i];
    }
    // for (ll i=0;i<N;i++){
    //     for (ll j=0;j<M;j++){
    //         cout << grid[i][j];
    //     }
    //     cout << endl;
    // }
    
    ll NN = N*M;
    DSU dsu(NN);
    for (ll i=0;i<N;i++){
        for (ll j=0;j<M;j++){
            for (ll k=0;k<4;k++){
                ll di = i + dxs[k];
                ll dj = j + dys[k];
                if (!bounds(di,dj)) continue;
                assert(i<N);
                assert(j<M);
                assert(i>=0);
                assert(j>=0);
                if (grid[i][j]=='.'){
                    dsu.join(comp(di,dj),comp(i,j));
                }
                else if (grid[i][j]=='R' && grid[di][dj]=='R'){
                    dsu.join(comp(di,dj),comp(i,j));
                }
                else if (grid[i][j]=='B' && grid[di][dj]=='B'){
                    dsu.join(comp(di,dj),comp(i,j));
                }
            }
        }
    }
    for (ll q=0;q<Q;q++){
        ll rs,cs,re,ce;cin>>rs>>cs>>re>>ce;
        ll u = comp(rs,cs);
        ll v = comp(re,ce);
        assert(u<NN);
        assert(v<NN);
        // cout << u << ' ' << v << endl;
        if (dsu.find(u)==dsu.find(v)){
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
}
int main(){
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T; while (T--) solve();
}