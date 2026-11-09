#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define foreach(v, a) for(auto &v : a)

const vector<pair<int, int>> dirs{{-1, 0},{1,0},{0,1},{0,-1}};

void dfs(int i, int j, int n, int m, vector<vector<bool>> &vis, vector<string> &grid){
    if(vis[i][j])
        return;
    vis[i][j] = true;
    
    for(auto dir : dirs){
        int x = i+dir.first;
        int y = j+dir.second;
        //cout << i << " " << j << " " << x << " " << y << endl;
        if(x < 0 || x >= n || y < 0 || y >= m)
            continue;
        
        if(grid[x][y] == '.' || grid[i][j] == '.' || grid[x][y] == grid[i][j] )
            dfs(x, y, n, m, vis, grid);
    }

}

void solve(){
    int n, m, q;
    cin >> n >> m >> q;
    vector<string> grid(n);
    foreach(row, grid){
        cin >> row;
    }

    vector<vector<bool>> vis(n, vector<bool>(m));
    dfs(n-1, m-1, n, m, vis, grid);

    for(int i = 0; i < q; i++){
        int rs, cs, re, ce;
        cin >> rs >> cs >> re >> ce;
        if(vis[rs][cs]){
            cout << "YES\n";
            continue;
        }
        cout << "NO\n";
    }
}   

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for(int i = 0; i < T; i++) 
        solve();
    return 0;
}