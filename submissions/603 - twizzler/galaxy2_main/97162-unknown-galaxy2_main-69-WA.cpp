#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> G(N);
        for (int i = 0; i < N; i++) cin >> G[i];

        vector<array<int, 5>> queries(Q);
        map<pair<int, int>, vector<int>> by_start;

        for (int i = 0; i < Q; i++) {
            int rs, cs, re, ce, k;
            cin >> rs >> cs >> re >> ce >> k;
            queries[i] = {rs, cs, re, ce, k};
            by_start[{rs, cs}].push_back(i);
        }

        vector<string> ans(Q);

        for (auto& [start, ids] : by_start) {
            int sr = start.first, sc = start.second;

            vector<vector<array<int, 2>>> dist(N, vector<array<int, 2>>(M, {INF, INF}));
            queue<tuple<int, int, int>> q;

            dist[sr][sc][0] = 0;
            q.emplace(sr, sc, 0);

            while (!q.empty()) {
                auto [r, c, mode] = q.front();
                q.pop();
                int d = dist[r][c][mode];

                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;

                    char tile = G[nr][nc];
                    bool can_stand = (tile == '.') ||
                                     (mode == 0 && tile == 'B') ||
                                     (mode == 1 && tile == 'R');

                    if (can_stand && dist[nr][nc][mode] == INF) {
                        dist[nr][nc][mode] = d + 1;
                        q.emplace(nr, nc, mode);
                    }
                }

                if (G[r][c] == '.' && dist[r][c][1 - mode] == INF) {
                    dist[r][c][1 - mode] = d + 1;
                    q.emplace(r, c, 1 - mode);
                }
            }

            for (int id : ids) {
                int re = queries[id][2];
                int ce = queries[id][3];
                int K  = queries[id][4];
                int best = min(dist[re][ce][0], dist[re][ce][1]);
                ans[id] = (best <= K ? "YES" : "NO");
            }
        }

        for (auto& s : ans) cout << s << '\n';
    }
    return 0;
}
