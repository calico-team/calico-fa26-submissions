#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define ull unsigned long long
#define pii pair<int, int>
#define pli pair<ll, int>
#define pll pair<ll, ll>
#define pb push_back
#define fi first
#define se second
#define cont continue
#define iMAXI 1e9
#define llMAXI 1e18
#define MOD7 1e9 + 7
#define MOD9 1e9 + 9
#define MODfft 998244353
#define decim(n) cout<<fixed<<setprecision(n)
#define CF int tt;cin>>tt;while(tt--)
#define sheesh ios::sync_with_stdio(0);cin.tie(0);
#define xingqiu return 0;

using namespace std;

struct DSU{
    int n;
    vector<int> par,sz;
 
    DSU(int _n){
        n = _n;
        par.resize(n);
        iota(par.begin(), par.end(), 0);
        sz.assign(n, 1);
    }
 
    int find(int u){
        return u == par[u] ? u : par[u] = find(par[u]);
    }
 
    bool merge(int u, int v){
        u = find(u), v = find(v);
 
        if(u == v) return 0;
        if(sz[u] > sz[v]) swap(u, v);
 
        par[u] = v;
        sz[v] += sz[u];
 
        return 1;
    }
};

int main(){

    sheesh

    int dr[4] = {1, -1, 0, 0}, 
        dc[4] = {0, 0, 1, -1};

    auto between = [](int r, int c, int n, int m){
        return (0 <= r && r < n) && (0 <= c && c < m);
    };

    auto coor_to_idx = [&](int r, int c, int m){
        return r*m + c;
    };

    auto idx_to_coor = [&](int idx, int m){
        return make_pair(idx / m, idx % m);
    };

    CF{
        int n,m,q;cin>>n>>m>>q;
        vector<string> grid(n);
        for(auto &gr : grid) cin>>gr;

        DSU dih(n*m);
        
        queue<pii> bfs;
        bfs.push({n - 1, m - 1});
        while(!bfs.empty()){
            auto [cur_r, cur_c] = bfs.front();
            bfs.pop();

            for(int i = 0; i < 4; i++){
                auto [next_r, next_c] = make_pair(cur_r + dr[i], cur_c + dc[i]);

                if(!between(next_r, next_c, n, m)) cont;
                if(dih.find(coor_to_idx(cur_r, cur_c, m)) == dih.find(coor_to_idx(next_r, next_c, m))) cont;
                if(grid[next_r][next_c] == grid[cur_r][cur_c] || grid[cur_r][cur_c] == '.' || grid[next_r][next_c] == '.'){
                    bfs.push({next_r, next_c});
                    dih.merge(coor_to_idx(cur_r, cur_c, m), coor_to_idx(next_r, next_c, m));
                }
            }
        }

        // for(int i = 0; i < n; i++){
        //     for(int j = 0; j < m; j++){
        //         cout << ok[i][j] << " ";
        //     }
        //     cout << "\n";
        // }

        while(q--){
            int a,b,c,d;cin>>a>>b>>c>>d;

            if(dih.find(coor_to_idx(a, b, m)) == dih.find(coor_to_idx(c, d, m))){
                cout << "YES\n";
            }else{
                bool ok = 0;
                for(int i = 0; i < 4; i++){
                    auto [next_r, next_c] = make_pair(a + dr[i], b + dc[i]);
                    if(between(next_r, next_c, n, m) && dih.find(coor_to_idx(next_r, next_c, m)) == dih.find(coor_to_idx(c, d, m))){
                        ok = 1;
                        break;
                    }
                }
                cout << (ok ? "YES" : "NO") << "\n";
            }
        }
    }

    xingqiu
}
