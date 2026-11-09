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

int main(){

    sheesh

    int dr[4] = {1, -1, 0, 0}, 
        dc[4] = {0, 0, 1, -1};

    auto between = [](int r, int c, int n, int m){
        return (0 <= r && r < n) && (0 <= c && c < m);
    };

    CF{
        int n,m,q;cin>>n>>m>>q;
        vector<string> grid(n);
        for(auto &gr : grid) cin>>gr;

        vector<vector<bool>> ok(n, vector<bool>(m, 0));
        
        queue<pii> bfs;
        ok[n - 1][m - 1] = 1;
        bfs.push({n - 1, m - 1});
        while(!bfs.empty()){
            auto [cur_r, cur_c] = bfs.front();
            bfs.pop();

            for(int i = 0; i < 4; i++){
                auto [next_r, next_c] = make_pair(cur_r + dr[i], cur_c + dc[i]);

                if(!between(next_r, next_c, n, m)) cont;
                if(ok[next_r][next_c]) cont;
                if(grid[next_r][next_c] == grid[cur_r][cur_c] || grid[cur_r][cur_c] == '.' || grid[next_r][next_c] == '.'){
                    bfs.push({next_r, next_c});
                    ok[next_r][next_c] = 1;
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

            cout << (ok[a][b] ? "YES" : "NO") << "\n";
        }
    }

    xingqiu
}
