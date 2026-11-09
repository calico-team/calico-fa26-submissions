#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<vector<char>> grid;
vector<vector<bool>> reach;
vector<pair<int, int>> dirs = {{1,0}, {0,1}, {-1,0} , {0,-1}};
void recur(int x, int y){
    if(reach[x][y]) return;
    reach[x][y] = true;
    char c = grid[x][y];
    for(pair<int, int> p : dirs){
        int nx = p.first + x;
        int ny = p.second + y;
        if(nx < 0 || nx >= n) continue;
        if(ny < 0 || ny >= m) continue;
        char nc = grid[nx][ny];
        if(c != '.' && nc != '.' && nc != c) continue;
        recur(nx, ny);
    }
}

void solve(){
    int q;
    cin >> n >> m >> q;
    grid = vector<vector<char>> (n, vector<char> (m));
    reach = vector<vector<bool>> (n, vector<bool> (m, false));
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            cin >> grid[i][j];
        }
    }
    recur(n-1, m-1);
    for(int i = 0; i<q; i++){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if(reach[a][b]) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}