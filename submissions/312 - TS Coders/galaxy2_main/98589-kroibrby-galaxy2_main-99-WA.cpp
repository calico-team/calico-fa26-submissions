#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, m, q; cin >> n >> m >> q;
        vector<string> g(n);
        for (auto &s : g) cin >> s;
        vector<array<int,5>> queries(q);
        unordered_map<int, vector<int>> byStart;
        byStart.reserve(q * 2);
        for (int i = 0; i < q; ++i) {
            auto &a = queries[i];
            cin >> a[0] >> a[1] >> a[2] >> a[3] >> a[4];
            byStart[a[0] * m + a[1]].push_back(i);
        }
        const int cells = n * m;
        const int INF = 1e9;
        vector<int> dist(2 * cells);
        vector<string> answer(q);
        auto active = [&](int cell, int mode) {
            char c = g[cell / m][cell % m];
            return c == '.' || (mode == 0 ? c == 'B' : c == 'R');
        };
        for (auto &entry : byStart) {
            int start = entry.first;
            fill(dist.begin(), dist.end(), INF);
            queue<int> bfs;
            int source = start; // blue mode is 0
            dist[source] = 0;
            bfs.push(source);
            while (!bfs.empty()) {
                int state = bfs.front(); bfs.pop();
                int mode = state / cells;
                int cell = state % cells;
                int r = cell / m, c = cell % m;
                int nd = dist[state] + 1;
                if (g[r][c] == '.') {
                    int ns = (1 - mode) * cells + cell;
                    if (dist[ns] == INF) { dist[ns] = nd; bfs.push(ns); }
                }
                const int dr[4] = {-1, 1, 0, 0};
                const int dc[4] = {0, 0, -1, 1};
                for (int z = 0; z < 4; ++z) {
                    int nr = r + dr[z], nc = c + dc[z];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                    int nextCell = nr * m + nc;
                    if (!active(nextCell, mode)) continue;
                    int ns = mode * cells + nextCell;
                    if (dist[ns] == INF) { dist[ns] = nd; bfs.push(ns); }
                }
            }
            for (int qi : entry.second) {
                auto &a = queries[qi];
                int dest = a[2] * m + a[3];
                int best = min(dist[dest], dist[cells + dest]);
                answer[qi] = best <= a[4] ? "YES" : "NO";
            }
        }
        for (auto &s : answer) cout << s << '\n';
    }
}
