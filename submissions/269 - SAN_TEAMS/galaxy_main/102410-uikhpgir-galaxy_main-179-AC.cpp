#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll vis[205][205];
int main() {
    ll t;
    cin >> t;
    while(t--) {
        ll n, m, Q;
        cin >> n >> m >> Q;
        vector<vector<char>> matriz(n, vector<char>(m));
        for(ll i = 0; i < n; i++) {
            for(ll j = 0; j < m; j++) {
                cin >> matriz[i][j];
                vis[i][j] = 0;
            }
        }
        ll dx[] = {-1, 1, 0, 0};
        ll dy[] = {0, 0, -1, 1};
        ll id = 0;
        for(ll i = 0; i < n; i++) {
            for(ll j = 0; j < m; j++) {
                if(vis[i][j] != 0) {
                    continue;
                }
                id++;
                queue<pair<ll,ll>> q;
                q.push({i,j});
                vis[i][j] = id;
                while(!q.empty()) {
                    auto [u,v] = q.front();
                    q.pop();
                    for(ll k = 0; k < 4; k++) {
                        ll x = u + dx[k];
                        ll y = v + dy[k];
                        if(x < 0 || x >= n || y < 0 || y >= m) {
                            continue;
                        }
                        if(vis[x][y] != 0) {
                            continue;
                        }
                        if(matriz[u][v] == 'R' && matriz[x][y] == 'B') {
                            continue;
                        }
                        if(matriz[u][v] == 'B' && matriz[x][y] == 'R') {
                            continue;
                        }
                        vis[x][y] = id;
                        q.push({x,y});
                    }
                }
            }
        }
        while(Q--) {
            ll r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;

            if(vis[r1][c1] == vis[r2][c2]) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
        }
    }
}