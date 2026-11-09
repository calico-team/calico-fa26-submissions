#include <bits/stdc++.h>

using namespace std;

int n, m, q;

typedef pair<int, int> pi;
typedef tuple<int, int, char> ti;

vector<pi> dirs = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

void dfs(int start_r, int start_c, vector<vector<char>>& grid, vector<vector<bool>>& seen){
    stack<ti> st;
    st.push({start_r, start_c, grid[start_r][start_c]});
    while (!st.empty()){
        auto [r, c, ch] = st.top(); st.pop();
        if (seen[r][c]) continue;
        seen[r][c] = 1;

        for (auto [dr, dc] : dirs){
            int nr = r + dr, nc = c + dc;

            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            char nch = grid[nr][nc];
            if (nch == 'R' && ch == 'B' || nch == 'B' && ch == 'R') continue;

            st.push({nr, nc, nch});
        }
    }
}

void solve(){
    cin >> n >> m >> q;
    vector<vector<char>> grid(n, vector<char>(m));
    vector<vector<bool>> seen(n, vector<bool>(m));
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++)
            cin >> grid[i][j];
    
    dfs(n-1, m-1, grid, seen);
    while (q--){
        int sr, sc, er, ec; cin >> sr >> sc >> er >> ec;
        if (seen[sr][sc]) cout << "YES\n";
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