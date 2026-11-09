#include <bits/stdc++.h>
using namespace std;
#define int int64_t 

using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vector<int>>;
using ll = long long;
using str = string;
using pi = array<int,2>;

#define sz(x) int(x.size())
#define lb lower_bound
#define ub upper_bound
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define pb push_back

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define rep(a) FOR(_, 0, a)

const int MOD = 998244353;
const int INF = 1e18;

constexpr int pcnt(int x) { return __builtin_popcountll(x);}

void solve() {
    int n, m, qr; cin >> n >> m >> qr;

    vvi g(n, vi (m));
    FOR (i, 0, n) {
        str s; cin >> s;
        FOR (j, 0, m) {
            if (s[j] == 'B') g[i][j] = 1;
            else if (s[j] == 'R') g[i][j] = 2;
            else g[i][j] = 0;
        }
    }

    vector<vector<int>> v(n, vi (m, 0));
    int nm = 1;

    FOR (z, 0, n) {
        FOR (w, 0, m) {

            if (v[z][w] != 0) continue;

            v[z][w] = nm; 

            queue<array<int,2>> q;
            q.push({z, w});

            vector<pi> dirs = {{-1,0}, {1, 0}, {0, -1}, {0, 1}};

            while (!q.empty()) {
                auto u = q.front();
                q.pop();

                for (auto d : dirs) {
                    int i = u[0] + d[0], j = u[1] + d[1];
                    if (i >= n or i < 0 or j >= m or j < 0 or v[i][j] != 0) continue;

                    if (g[u[0]][u[1]] == 0) { 
                        v[i][j] = v[u[0]][u[1]];
                        q.push({i, j});
                    } else if (g[u[0]][u[1]] == 1 and (g[i][j] == 1 or g[i][j] == 0)) {
                        v[i][j] = v[u[0]][u[1]];
                        q.push({i, j});
                    } else if (g[u[0]][u[1]] == 2 and (g[i][j] == 2 or g[i][j] == 0)) {
                        v[i][j] = v[u[0]][u[1]];
                        q.push({i, j});
                    }
                }
            }

            nm++;
        }
    }

    while (qr--) {
        int i, j, g; cin >> i >> j >> g >> g;
        if (v[i][j] == v[n - 1][m - 1]) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        solve();
    }
}


