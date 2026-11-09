#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
void solve() {
    int N, M, Q;
    if (!(cin >> N >> M >> Q)) return;
    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
    }
    map<pair<int, int>, vector<vector<vector<ll>>>> memo;
    auto get_dist = [&](int sr, int sc) {
        if (memo.count({sr, sc})) {
            return memo[{sr, sc}];
        }
        vector<vector<vector<ll>>> dist(2, vector<vector<ll>>(N, vector<ll>(M, INF)));
        queue<tuple<int, int, int>> q;
        dist[0][sr][sc] = 0;
        q.push({sr, sc, 0});
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        while (!q.empty()) {
            auto [r, c, m] = q.front();
            q.pop();
            ll d = dist[m][r][c];
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                    char cell = grid[nr][nc];
                    bool active = false;
                    if (cell == '.') active = true;
                    else if (cell == 'B' && m == 0) active = true;
                    else if (cell == 'R' && m == 1) active = true;
                    if (active) {
                        if (dist[m][nr][nc] > d + 1) {
                            dist[m][nr][nc] = d + 1;
                            q.push({nr, nc, m});
                        }
                    }
                }
            }
            if (grid[r][c] == '.') {
                int nm = 1 - m;
                if (dist[nm][r][c] > d + 1) {
                    dist[nm][r][c] = d + 1;
                    q.push({r, c, nm});
                }
            }
        }
        memo[{sr, sc}] = dist;
        return dist;
    };
    for (int i = 0; i < Q; ++i) {
        int r1, c1, r2, c2;
        ll K;
        cin >> r1 >> c1 >> r2 >> c2 >> K;
        auto dist = get_dist(r1, c1);
        ll min_d = min(dist[0][r2][c2], dist[1][r2][c2]);
        if (min_d <= K) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) solve();
    }
}