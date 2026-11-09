#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX = 2e5 +5, MOD = 2e9 +7, MKX = 4e5;
const ll MTX = 1e18 +1;

bool vis[40204];
vector <int> adj[40204];

void dfs(int u){
    vis[u] = true;

    for(int v : adj[u]){
        if(!vis[v]) dfs(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--){
        char c[204][204];
        int a[204][204];
        
        int n, m, q;
        cin >> n >> m >> q;

        for(int i=0; i<40204; i++){
            adj[i].clear();
        }

        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                cin >> c[i][j];
                a[i][j] = i*m +j;

                if(c[i][j] == '.'){
                    if(i>0){
                        adj[a[i][j]].push_back(a[i-1][j]);
                        adj[a[i-1][j]].push_back(a[i][j]);
                    }
                    if(j>0){
                        adj[a[i][j]].push_back(a[i][j-1]);
                        adj[a[i][j-1]].push_back(a[i][j]);
                    }
                }

                if(c[i][j] == 'R'){
                    if(i>0 && c[i-1][j] != 'B'){
                        adj[a[i][j]].push_back(a[i-1][j]);
                        adj[a[i-1][j]].push_back(a[i][j]);
                    }
                    if(j>0 && c[i][j-1] != 'B'){
                        adj[a[i][j]].push_back(a[i][j-1]);
                        adj[a[i][j-1]].push_back(a[i][j]);
                    }
                }

                if(c[i][j] == 'B'){
                    if(i>0 && c[i-1][j] != 'R'){
                        adj[a[i][j]].push_back(a[i-1][j]);
                        adj[a[i-1][j]].push_back(a[i][j]);
                    }
                    if(j>0 && c[i][j-1] != 'R'){
                        adj[a[i][j]].push_back(a[i][j-1]);
                        adj[a[i][j-1]].push_back(a[i][j]);
                    }
                }
            }
        }

        

        for(int i=0; i<q; i++){
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            int x = x1*m + y1, y = x2*m +y2;

            for(int i=0; i<40204; i++){
                vis[i] = false;
            }

            dfs(x);
            if(vis[y]) cout << "YES\n";
            else cout << "NO\n";
        }

    }
    
    return 0;
}