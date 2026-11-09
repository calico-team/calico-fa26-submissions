#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int DR[] = {-1, 1, 0, 0};
    const int DC[] = {0, 0, -1, 1};
    const int INF = 1e9;

    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> G(N);
        for (int i = 0; i < N; ++i) cin >> G[i];

        struct Query {
            int sr, sc, er, ec, K;
        };
        vector<Query> queries(Q);
        for (int i = 0; i < Q; ++i) {
            cin >> queries[i].sr >> queries[i].sc
                >> queries[i].er >> queries[i].ec >> queries[i].K;
        }

        // Group queries by starting cell
        map<pair<int,int>, vector<int>> groups;
        for (int i = 0; i < Q; ++i) {
            groups[{queries[i].sr, queries[i].sc}].push_back(i);
        }

        vector<string> answer(Q, "NO");
        // dist[mode][r][c]
        vector<vector<vector<int>>> dist(2,
            vector<vector<int>>(N, vector<int>(M, -1)));

        for (auto& [start, ids] : groups) {
            int sr = start.first, sc = start.second;

            // reset distances
            for (int m = 0; m < 2; ++m)
                for (int r = 0; r < N; ++r)
                    fill(dist[m][r].begin(), dist[m][r].end(), -1);

            queue<tuple<int,int,int>> q; // r, c, mode
            q.emplace(sr, sc, 0);
            dist[0][sr][sc] = 0;

            while (!q.empty()) {
                auto [r, c, mode] = q.front();
                q.pop();
                int d = dist[mode][r][c];

                // spin (only on '.')
                if (G[r][c] == '.') {
                    int nmode = 1 - mode;
                    if (dist[nmode][r][c] == -1) {
                        dist[nmode][r][c] = d + 1;
                        q.emplace(r, c, nmode);
                    }
                }

                // four-directional moves
                for (int k = 0; k < 4; ++k) {
                    int nr = r + DR[k];
                    int nc = c + DC[k];
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;

                    char ch = G[nr][nc];
                    bool can = (ch == '.') ||
                               (mode == 0 && ch == 'B') ||
                               (mode == 1 && ch == 'R');
                    if (can && dist[mode][nr][nc] == -1) {
                        dist[mode][nr][nc] = d + 1;
                        q.emplace(nr, nc, mode);
                    }
                }
            }

            // answer all queries that share this start
            for (int id : ids) {
                const auto& qr = queries[id];
                int D = INF;

                for (int mode = 0; mode < 2; ++mode) {
                    char ch = G[qr.er][qr.ec];
                    bool can = (ch == '.') ||
                               (mode == 0 && ch == 'B') ||
                               (mode == 1 && ch == 'R');
                    if (can && dist[mode][qr.er][qr.ec] != -1) {
                        D = min(D, dist[mode][qr.er][qr.ec]);
                    }
                }

                if (D != INF && D <= qr.K && (qr.K - D) % 2 == 0) {
                    answer[id] = "YES";
                }
            }
        }

        for (const string& s : answer) cout << s << '\n';
    }
    return 0;
}