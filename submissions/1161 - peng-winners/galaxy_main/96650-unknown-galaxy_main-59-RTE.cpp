#include <bits/stdc++.h>

using namespace std;

int n, m, q;

typedef pair<int, int> pi;
typedef tuple<int, int, char> ti;

vector<pi> dirs = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

struct DSU{
    vector<int> par;

    DSU(int n){
        par.resize(n);
        for (int i = 0; i < n; i++) par[i] = i;
    }

    int find(int x){
        if (par[x] == x) return x;
        return par[x] = find(par[x]);
    }

    void unite(int x, int y){
        x = find(x);
        y = find(y);
        if (x != y) par[x] = y;
    }
};

void dfs(int start_r, int start_c, vector<vector<char>>& grid, DSU& dsu){
    int idx = start_r * n + start_c;
    vector<vector<bool>> seen(n, vector<bool>(m));
    stack<ti> st;
    st.push({start_r, start_c, grid[start_r][start_c]});
    while (!st.empty()){
        auto [r, c, ch] = st.top(); st.pop();
        if (seen[r][c]) continue;
        seen[r][c] = 1;

        //cout << r << ' ' << c << '\n';

        for (auto [dr, dc] : dirs){
            int nr = r + dr, nc = c + dc;

            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            char nch = grid[nr][nc];
            if (nch == 'R' && ch == 'B' || nch == 'B' && ch == 'R') continue;

            dsu.unite(idx, nr*n + nc);
            st.push({nr, nc, nch});
        }
    }
}

void solve(){
    cin >> n >> m >> q;
    DSU dsu(n*m);
    vector<vector<char>> grid(n, vector<char>(m));
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++)
            cin >> grid[i][j];
    
    dfs(n-1, m-1, grid, dsu);
    while (q--){
        int sr, sc, er, ec; cin >> sr >> sc >> er >> ec;
        int start_idx = sr*n + sc, end_idx = er*n + ec;
        if (dsu.find(start_idx) == dsu.find(end_idx)) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t--){
        solve();
    }
    return 0;
}