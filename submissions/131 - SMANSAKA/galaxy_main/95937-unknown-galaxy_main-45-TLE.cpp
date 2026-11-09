#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    if (!(cin >>t)) return 0;
    while (t--) {
        int n,m,q;
        cin >> n >>m >> q;
        vector<string> g(n);
        for (int i = 0; i < n; i++) cin >> g[i];

        int dr[] = {-1,1, 0,0};
        int dc[] = {0, 0,-1,1};

        for (int i = 0; i <q; i++) {
            int r1, c1,r2, c2;
            cin >> r1 >> c1>>r2 >> c2;

            // state ada 2 * n * m, pakai visited 3d, cobain dulu aja semisal bisa
            vector<vector<vector<bool>>> vis(2, vector<vector<bool>>(n, vector<bool>(m, false)));
            queue<tuple<int, int, int>>qb;

            qb.push({r1, c1,0});
            vis[0][r1][c1] =true;

            bool ok =false;
            while (!qb.empty()) {
                auto [r, c, md] = qb.front();
                qb.pop();

                if (r ==r2 && c ==c2) {
                    ok =true;
                    break;
                }

                if (g[r][c] == '.' && !vis[1 - md][r][c]) {
                    vis[1 - md][r][c] =true;
                    qb.push({r, c, 1 - md});
                }

                // jalan ke tetangga sbelah
                for (int d = 0; d <4; d++) {
                    int nr = r + dr[d], nc =c+ dc[d];
                    if (nr < 0 || nr >= n ||nc <0 || nc >= m) continue;
                    char ch =g[nr][nc];
                    bool active =(ch == '.' || (md == 0 && ch == 'B') || (md == 1 && ch == 'R'));
                    if (!active) continue;

                    if (!vis[md][nr][nc]) {
                        vis[md][nr][nc] =true;
                        qb.push({nr, nc, md});
                    }
                }
            }

            if (ok) cout <<"YES\n";
            else cout << "NO\n";
        }
    }
    // bismillah 
    return 0;
}