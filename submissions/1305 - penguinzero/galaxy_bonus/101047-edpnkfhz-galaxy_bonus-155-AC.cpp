#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

int n, m, id;
string g[205];
int comp[205][205][2];

void dfs(int r, int c, int mode){
    if(r < 0 || r >= n || c < 0 || c >= m){
        return;
    }
    if(g[r][c] == 'R' && mode == 0){
        return;
    }
    if(g[r][c] == 'B' && mode == 1){
        return;
    }
    if(comp[r][c][mode] != -1){
        return;
    }
    comp[r][c][mode] = id;

    dfs(r+1,c,mode);
    dfs(r-1,c,mode);
    dfs(r,c+1,mode);
    dfs(r,c-1,mode);
    if(g[r][c] == '.'){
        dfs(r,c, 1 - mode);
    }
}
int main() {
    int t;
    cin >> t;
    for(int z = 0; z < t; z++){
        int q;
        cin >> n >> m >> q;
        for(int i = 0; i < n; i++){
            cin >> g[i];
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                comp[i][j][0] = -1;
                comp[i][j][1] = -1;
            }
        }
        id = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                for(int mode = 0; mode < 2; mode++){
                    if(comp[i][j][mode] == -1){
                        dfs(i, j, mode);
                        id++;
                    }
                }
            }
        }
        for(int i = 0; i < q; i++){
            int rs, cs, re, ce;
            cin >> rs >> cs >> re >> ce;
            int start = comp[rs][cs][0];
            if(start == comp[re][ce][0] || start == comp[re][ce][1]){
                cout << "YES" << '\n';
            }else{
                cout << "NO" << '\n';
            }
        }
    }
}
