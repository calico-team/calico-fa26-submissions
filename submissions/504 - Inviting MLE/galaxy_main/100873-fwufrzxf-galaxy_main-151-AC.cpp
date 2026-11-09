#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;


struct DSU{
    int n;
    vector<int> p,sz;
    DSU(int k) : n(k), p(n,0), sz(n,1){
        for(int i=0; i<n; i++) p[i] = i;
    }
    
    int find(int u){
        if(p[u] == u) return u;
        return find(p[u]);
    }

    void unite(int u,int v){
        u = find(u);
        v = find(v);
        if(u == v) return;
        if(sz[u] < sz[v]) swap(u,v);
        p[v] = u;
        sz[u] += sz[v];
    }

    bool same(int u,int v){
        return find(u) == find(v);
    }
};

void solve(){

    int n,m,q; cin >> n >> m >> q;
    vector<vector<int>> grid(n,vector<int>(m));

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            char c; cin >> c;
            if(c == 'R'){
                grid[i][j] = 1;
            }else if(c == 'B'){
                grid[i][j] = -1;
            }else{
                grid[i][j] = 0;
            }
        }
    }

    DSU dsu(n*m);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(i-1 >= 0 && grid[i][j]*grid[i-1][j] >= 0){
                dsu.unite(i*m+j, (i-1)*m+j);
            }
            if(j-1 >= 0 && grid[i][j]*grid[i][j-1] >= 0){
                dsu.unite(i*m+j, i*m+(j-1));
            }
        }
    }

    while(q--){
        int rs,cs,re,ce; cin >> rs >> cs >>re >> ce;
        if(dsu.same(rs*m+cs,re*m+ce)){
            cout << "YES\n";
        }else{
            cout << "NO\n";
        }
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--){
        solve();
    }

}   