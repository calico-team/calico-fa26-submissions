#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n) : p(n) { iota(p.begin(), p.end(), 0); }
    int find(int x) {
        while (p[x] != x) { p[x] = p[p[x]]; x = p[x]; }
        return x;
    }
    void uni(int a, int b) {
        a = find(a); b = find(b);
        if (a != b) p[a] = b;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    string out;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> g(N);
        for (auto &row : g) cin >> row;

        const int cells = N * M;
        const int S = 2 * cells;

        // bit 0 = blue, bit 1 = red
        vector<unsigned char> act(cells);
        vector<int> rowOf(cells), colOf(cells);
        for (int r = 0; r < N; r++)
            for (int c = 0; c < M; c++) {
                int id = r * M + c;
                rowOf[id] = r;
                colOf[id] = c;
                char x = g[r][c];
                act[id] = (x == '.') ? 3 : (x == 'B') ? 1 : 2;
            }

        vector<int> rs(Q), cs(Q), re(Q), ce(Q);
        vector<long long> K(Q);
        vector<char> ans(Q, 0);
        vector<int> big, small;

        for (int i = 0; i < Q; i++) {
            cin >> rs[i] >> cs[i] >> re[i] >> ce[i] >> K[i];
            if (K[i] >= S) big.push_back(i);
            else small.push_back(i);
        }

        // large K: connectivity is all that matters
        if (!big.empty()) {
            DSU dsu(S);
            for (int u = 0; u < cells; u++) {
                if (act[u] == 3) dsu.uni(2 * u, 2 * u + 1);
                int r = rowOf[u], c = colOf[u];
                int nb[2] = {(c + 1 < M) ? u + 1 : -1,
                             (r + 1 < N) ? u + M : -1};
                for (int v : nb) {
                    if (v < 0) continue;
                    for (int m = 0; m < 2; m++)
                        if (((act[u] >> m) & 1) && ((act[v] >> m) & 1))
                            dsu.uni(2 * u + m, 2 * v + m);
                }
            }
            for (int qi : big) {
                int s = rs[qi] * M + cs[qi];
                int e = re[qi] * M + ce[qi];
                int root = dsu.find(2 * s);
                bool ok = ((act[e] & 1) && dsu.find(2 * e) == root) ||
                          ((act[e] & 2) && dsu.find(2 * e + 1) == root);
                ans[qi] = ok ? 1 : 0;
            }
        }

        // small K: BFS per distinct start
        vector<vector<int>> byStart(cells);
        for (int qi : small) byStart[rs[qi] * M + cs[qi]].push_back(qi);

        vector<int> stamp(S, 0), dist(S), q(S);
        int cur = 0;

        for (int s = 0; s < cells; s++) {
            if (byStart[s].empty()) continue;

            long long cap = 0;
            for (int qi : byStart[s]) cap = max(cap, K[qi]);

            ++cur;
            int head = 0, tail = 0;
            int st = 2 * s;
            stamp[st] = cur;
            dist[st] = 0;
            q[tail++] = st;

            while (head < tail) {
                int u = q[head++];
                int d = dist[u];
                if ((long long)d >= cap) break;

                int cell = u >> 1;
                int m = u & 1;
                int r = rowOf[cell], c = colOf[cell];

                if (act[cell] == 3) {
                    int v = u ^ 1;
                    if (stamp[v] != cur) {
                        stamp[v] = cur;
                        dist[v] = d + 1;
                        q[tail++] = v;
                    }
                }

                int nb[4];
                int cnt = 0;
                if (r > 0)     nb[cnt++] = cell - M;
                if (r + 1 < N) nb[cnt++] = cell + M;
                if (c > 0)     nb[cnt++] = cell - 1;
                if (c + 1 < M) nb[cnt++] = cell + 1;

                for (int k = 0; k < cnt; k++) {
                    int nc = nb[k];
                    if (!((act[nc] >> m) & 1)) continue;
                    int v = (nc << 1) | m;
                    if (stamp[v] != cur) {
                        stamp[v] = cur;
                        dist[v] = d + 1;
                        q[tail++] = v;
                    }
                }
            }

            for (int qi : byStart[s]) {
                int e = re[qi] * M + ce[qi];
                long long best = LLONG_MAX;
                for (int m = 0; m < 2; m++) {
                    int v = 2 * e + m;
                    if (((act[e] >> m) & 1) && stamp[v] == cur)
                        best = min(best, (long long)dist[v]);
                }
                ans[qi] = (best <= K[qi]) ? 1 : 0;
            }
        }

        for (int i = 0; i < Q; i++) out += ans[i] ? "YES\n" : "NO\n";
    }

    cout << out;
    return 0;
}