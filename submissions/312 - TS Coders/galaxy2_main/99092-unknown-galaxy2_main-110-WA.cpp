#include <bits/stdc++.h>
using namespace std;

struct Query {
    int sr, sc, tr, tc;
    int k;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> grid(N);
        for (auto &row : grid) cin >> row;

        vector<Query> queries(Q);
        unordered_map<int, vector<int>> grouped;
        grouped.reserve(Q * 2 + 1);
        for (int i = 0; i < Q; ++i) {
            auto &q = queries[i];
            cin >> q.sr >> q.sc >> q.tr >> q.tc >> q.k;
            grouped[q.sr * M + q.sc].push_back(i);
        }

        const int cells = N * M;
        const int states = cells * 2;
        const int INF = 1e9;
        vector<int> dist(states, INF);
        vector<string> answer(Q, "NO");
        vector<int> targetMark(cells, -1);
        vector<int> targetDist(cells, INF);
        vector<int> stamp(cells, 0);
        int runId = 0;
        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};

        auto active = [&](int cell, int mode) {
            char ch = grid[cell / M][cell % M];
            if (ch == '.') return true;
            return mode == 0 ? ch == 'B' : ch == 'R';
        };

        for (const auto &entry : grouped) {
            int start = entry.first;
            const vector<int> &ids = entry.second;
            ++runId;
            int maxK = 0;
            int remainingTargets = 0;
            for (int qi : ids) {
                maxK = max(maxK, queries[qi].k);
                int dest = queries[qi].tr * M + queries[qi].tc;
                if (stamp[dest] != runId) {
                    stamp[dest] = runId;
                    targetDist[dest] = INF;
                    ++remainingTargets;
                }
            }

            fill(dist.begin(), dist.end(), INF);
            queue<int> bfs;
            dist[start] = 0; // mode 0 = blue
            bfs.push(start);

            while (!bfs.empty() && remainingTargets > 0) {
                int state = bfs.front();
                bfs.pop();
                int d = dist[state];
                if (d >= maxK) continue;
                int mode = state / cells;
                int cell = state % cells;
                int r = cell / M, c = cell % M;

                if (targetDist[cell] == INF && stamp[cell] == runId) {
                    targetDist[cell] = d;
                    --remainingTargets;
                }

                int nd = d + 1;
                if (grid[r][c] == '.') {
                    int ns = (1 - mode) * cells + cell;
                    if (dist[ns] == INF) {
                        dist[ns] = nd;
                        bfs.push(ns);
                    }
                }

                for (int z = 0; z < 4; ++z) {
                    int nr = r + dr[z], nc = c + dc[z];
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
                    int nextCell = nr * M + nc;
                    if (!active(nextCell, mode)) continue;
                    int ns = mode * cells + nextCell;
                    if (dist[ns] == INF) {
                        dist[ns] = nd;
                        bfs.push(ns);
                    }
                }
            }

            for (int qi : ids) {
                const Query &q = queries[qi];
                int dest = q.tr * M + q.tc;
                int best = targetDist[dest];
                // A destination may be reached in either mode. If it was not
                // encountered as a popped state, use the completed distances.
                best = min(dist[dest], dist[cells + dest]);
                answer[qi] = (best <= q.k ? "YES" : "NO");
            }
        }

        for (const string &s : answer) cout << s << '\n';
    }
}
