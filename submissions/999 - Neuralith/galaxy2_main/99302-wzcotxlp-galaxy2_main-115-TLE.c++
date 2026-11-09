#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int DR[4] = {-1, 1, 0, 0};
    const int DC[4] = {0, 0, -1, 1};

    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> G(N);
        for (int i = 0; i < N; ++i) cin >> G[i];

        struct Query {
            int sr, sc, er, ec, K, id;
        };
        vector<Query> queries(Q);
        for (int i = 0; i < Q; ++i) {
            cin >> queries[i].sr >> queries[i].sc
                >> queries[i].er >> queries[i].ec >> queries[i].K;
            queries[i].id = i;
        }

        // group by start cell
        map<pair<int,int>, vector<Query>> groups;
        for (const auto& q : queries)
            groups[{q.sr, q.sc}].push_back(q);

        vector<string> answer(Q, "NO");

        // flat distance: mode * N * M + r * M + c
        const int SZ = 2 * N * M;
        vector<int> dist(SZ, -1);
        vector<int> stamp(SZ, 0);
        int timer = 1;

        auto idx = [&](int mode, int r, int c) {
            return mode * N * M + r * M + c;
        };

        for (auto& [start, qs] : groups) {
            int sr = start.first, sc = start.second;
            ++timer;   // new BFS epoch

            queue<tuple<int,int,int>> q; // r, c, mode
            q.emplace(sr, sc, 0);
            dist[idx(0, sr, sc)] = 0;
            stamp[idx(0, sr, sc)] = timer;

            while (!q.empty()) {
                auto [r, c, mode] = q.front();
                q.pop();
                int d = dist[idx(mode, r, c)];

                // spin
                if (G[r][c] == '.') {
                    int nmode = 1 - mode;
                    int id = idx(nmode, r, c);
                    if (stamp[id] != timer) {
                        stamp[id] = timer;
                        dist[id] = d + 1;
                        q.emplace(r, c, nmode);
                    }
                }

                // moves
                for (int k = 0; k < 4; ++k) {
                    int nr = r + DR[k];
                    int nc = c + DC[k];
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;

                    char ch = G[nr][nc];
                    bool can = (ch == '.') ||
                               (mode == 0 && ch == 'B') ||
                               (mode == 1 && ch == 'R');
                    if (!can) continue;

                    int id = idx(mode, nr, nc);
                    if (stamp[id] != timer) {
                        stamp[id] = timer;
                        dist[id] = d + 1;
                        q.emplace(nr, nc, mode);
                    }
                }
            }

            // answer all queries with this start
            for (const auto& qr : qs) {
                int D = INT_MAX;
                for (int mode = 0; mode < 2; ++mode) {
                    char ch = G[qr.er][qr.ec];
                    bool can = (ch == '.') ||
                               (mode == 0 && ch == 'B') ||
                               (mode == 1 && ch == 'R');
                    if (!can) continue;
                    int id = idx(mode, qr.er, qr.ec);
                    if (stamp[id] == timer)
                        D = min(D, dist[id]);
                }
                if (D != INT_MAX && D <= qr.K)
                    answer[qr.id] = "YES";
            }
        }

        for (const string& s : answer)
            cout << s << '\n';
    }
    return 0;
}