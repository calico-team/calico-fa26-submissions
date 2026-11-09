#include <bits/stdc++.h>
using namespace std;

int n, m, q;
char grid[200][200];
int gridset[200][200];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

void dfs(int r, int c, int set) {
    gridset[r][c] = set;
    for (int i = 0; i < 4; i++) {
        int newr = r + dx[i];
        int newc = c + dy[i];
        if (!(newr >= 0 && newr < n && newc >= 0 && newc < m)) continue;
        if (gridset[newr][newc] != -1) continue;
        
        if (grid[r][c] == grid[newr][newc] || grid[r][c] == '.' || grid[newr][newc] == '.')
            dfs(newr, newc, set);
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
                gridset[i][j] = -1;
            }
        }
        int curset = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (gridset[i][j] == -1) {
                    dfs(i, j, curset);
                    curset++;
                }
            }
        }
        /*/
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) cout << gridset[i][j] << " ";
            cout << endl;
        }
        //*/
        
        for (int i = 0; i < q; i++) {
            int rs, cs, re, ce;
            cin >> rs >> cs >> re >> ce;
            if (gridset[rs][cs] == gridset[re][ce]) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    
}