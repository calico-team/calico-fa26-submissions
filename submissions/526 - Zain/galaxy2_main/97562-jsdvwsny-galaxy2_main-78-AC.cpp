
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    const int INF = 1000000000;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> grid(N);
        for (auto &row : grid) cin >> row;

        int V = 2 * N * M;
        int W = 2 * N;

        int levels = 0;
        for (int t = M; t > 0; t /= 2)
            levels++;

        auto id = [M](int r, int c, int mode) {
            return 2 * (r * M + c) + mode;
        };

        auto allowed = [](char tile, int mode) {
            return tile == '.' ||
                   (tile == 'B' && mode == 0) ||
                   (tile == 'R' && mode == 1);
        };

        vector<array<int, 5>> adj(V);
        vector<unsigned char> degree(V, 0);
        vector<int> column(V);

        const int dr[4] = {1, -1, 0, 0};
        const int dc[4] = {0, 0, 1, -1};

        // Build the graph of positions and modes.
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                for (int mode = 0; mode < 2; mode++) {
                    int u = id(r, c, mode);
                    column[u] = c;

                    if (!allowed(grid[r][c], mode))
                        continue;

                    // Spin on normal tiles.
                    if (grid[r][c] == '.')
                        adj[u][degree[u]++] = u ^ 1;

                    // Walk to neighboring cells.
                    for (int d = 0; d < 4; d++) {
                        int nr = r + dr[d];
                        int nc = c + dc[d];

                        if (nr < 0 || nr >= N ||
                            nc < 0 || nc >= M)
                            continue;

                        if (allowed(grid[nr][nc], mode))
                            adj[u][degree[u]++] =
                                id(nr, nc, mode);
                    }
                }
            }
        }

        // Distances to separator-column states.
        vector<int> dist(
            (size_t)levels * V * W, INF
        );

        vector<int> bfs(V);

        auto build = [&](auto&& self, int l, int r,
                         int depth) -> void {
            if (l > r) return;

            int mid = (l + r) / 2;
            size_t offset = (size_t)depth * V * W;

            for (int row = 0; row < N; row++) {
                for (int mode = 0; mode < 2; mode++) {
                    if (!allowed(grid[row][mid], mode))
                        continue;

                    int slot = row * 2 + mode;
                    int src = id(row, mid, mode);

                    int head = 0, tail = 0;

                    dist[offset + (size_t)src * W + slot] = 0;
                    bfs[tail++] = src;

                    while (head < tail) {
                        int u = bfs[head++];
                        int nd = dist[
                            offset + (size_t)u * W + slot
                        ] + 1;

                        for (int j = 0; j < degree[u]; j++) {
                            int v = adj[u][j];

                            if (column[v] < l ||
                                column[v] > r)
                                continue;

                            size_t idx =
                                offset + (size_t)v * W + slot;

                            if (dist[idx] == INF) {
                                dist[idx] = nd;
                                bfs[tail++] = v;
                            }
                        }
                    }
                }
            }

            self(self, l, mid - 1, depth + 1);
            self(self, mid + 1, r, depth + 1);
        };

        build(build, 0, M - 1, 0);

        // Answer queries using precomputed distances.
        while (Q--) {
            int sr, sc, er, ec;
            long long K;

            cin >> sr >> sc >> er >> ec >> K;

            int u = id(sr, sc, 0);
            int v0 = id(er, ec, 0);
            int v1 = v0 + 1;

            int best = INF;
            int l = 0, r = M - 1, depth = 0;

            while (l <= r) {
                int mid = (l + r) / 2;

                size_t offset = (size_t)depth * V * W;

                const int* from =
                    dist.data() + offset + (size_t)u * W;

                const int* to0 =
                    dist.data() + offset + (size_t)v0 * W;

                const int* to1 =
                    dist.data() + offset + (size_t)v1 * W;

                for (int s = 0; s < W; s++) {
                    int d2 = min(to0[s], to1[s]);

                    if (from[s] != INF && d2 != INF)
                        best = min(best, from[s] + d2);
                }

                if (sc == mid || ec == mid)
                    break;

                if (sc < mid && ec < mid)
                    r = mid - 1;
                else if (sc > mid && ec > mid)
                    l = mid + 1;
                else
                    break;

                depth++;
            }

            cout << (best != INF && best <= K
                     ? "YES\n" : "NO\n");
        }
    }

    return 0;
}
