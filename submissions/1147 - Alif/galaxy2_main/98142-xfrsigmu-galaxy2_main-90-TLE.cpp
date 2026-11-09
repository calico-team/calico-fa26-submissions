#include <bits/stdc++.h>
using namespace std;

static inline bool walkable(char ch, int mode) {
    return ch == '.' || (ch == 'B' && mode == 0) || (ch == 'R' && mode == 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> g(N);
        for (auto &row : g) cin >> row;

        int cells = N * M;
        vector<int> rs(Q), cs(Q), re(Q), ce(Q);
        vector<long long> K(Q);
        vector<vector<int>> byStart(cells);

        for (int i = 0; i < Q; i++) {
            cin >> rs[i] >> cs[i] >> re[i] >> ce[i] >> K[i];
            byStart[rs[i] * M + cs[i]].push_back(i);
        }

        vector<char> ans(Q);
        vector<int> dist(2 * cells);
        vector<int> q(2 * cells);

        vector<char> cell(cells);
        for (int r = 0; r < N; r++)
            for (int c = 0; c < M; c++)
                cell[r * M + c] = g[r][c];

        const int dr[4] = {1, -1, 0, 0};
        const int dc[4] = {0, 0, 1, -1};

        for (int s = 0; s < cells; s++) {
            if (byStart[s].empty()) continue;

            long long cap = 0;
            for (int qi : byStart[s]) cap = max(cap, K[qi]);

            fill(dist.begin(), dist.end(), -1);
            int head = 0, tail = 0;
            int st = 2 * s;
            dist[st] = 0;
            q[tail++] = st;

            while (head < tail) {
                int u = q[head++];
                int d = dist[u];
                if ((long long)d >= cap) break;

                int c0 = u >> 1;
                int m = u & 1;
                int r = c0 / M, c = c0 % M;

                if (cell[c0] == '.') {
                    int v = u ^ 1;
                    if (dist[v] < 0) {
                        dist[v] = d + 1;
                        q[tail++] = v;
                    }
                }

                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k], nc = c + dc[k];
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
                    int nidx = nr * M + nc;
                    if (!walkable(cell[nidx], m)) continue;
                    int v = (nidx << 1) | m;
                    if (dist[v] < 0) {
                        dist[v] = d + 1;
                        q[tail++] = v;
                    }
                }
            }

            for (int qi : byStart[s]) {
                int e = re[qi] * M + ce[qi];
                long long best = LLONG_MAX;
                for (int m = 0; m < 2; m++) {
                    if (walkable(cell[e], m) && dist[2 * e + m] >= 0)
                        best = min(best, (long long)dist[2 * e + m]);
                }
                ans[qi] = (best <= K[qi]) ? 1 : 0;
            }
        }

        for (int i = 0; i < Q; i++)
            cout << (ans[i] ? "YES" : "NO") << '\n';
    }
    return 0;
}