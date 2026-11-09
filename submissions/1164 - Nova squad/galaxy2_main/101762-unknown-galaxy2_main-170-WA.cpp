#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<string> G;
struct Query { int rs, cs, re, ce; long long K; };
vector<Query> qs;
vector<char> ans;
const int INF = 0x3f3f3f3f;

inline bool active(int r, int c, int mode) {
    char ch = G[r][c];
    if (ch == '.') return true;
    if (ch == 'B') return mode == 0;
    return mode == 1;
}

void solve(int l, int r, vector<int> &ids) {
    if (l > r || ids.empty()) return;
    int mid = (l + r) / 2;
    int W = r - l + 1;
    int S = N * W * 2;

    vector<int> L, R, here;
    for (int id : ids) {
        int a = min(qs[id].cs, qs[id].ce), b = max(qs[id].cs, qs[id].ce);
        if (b < mid) L.push_back(id);
        else if (a > mid) R.push_back(id);
        else here.push_back(id);
    }

    if (!here.empty()) {
        auto idx = [&](int row, int col, int mode) {
            return ((row * W) + (col - l)) * 2 + mode;
        };

        vector<vector<int>> D;
        const int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
        for (int row = 0; row < N; row++) {
            for (int mode = 0; mode < 2; mode++) {
                if (!active(row, mid, mode)) continue;
                vector<int> dist(S, INF);
                vector<int> q;
                q.reserve(S);
                int s0 = idx(row, mid, mode);
                dist[s0] = 0;
                q.push_back(s0);
                for (size_t h = 0; h < q.size(); h++) {
                    int cur = q[h];
                    int m = cur & 1;
                    int cell = cur >> 1;
                    int cr = cell / W, cc = cell % W + l;
                    int d = dist[cur];
                    for (int k = 0; k < 4; k++) {
                        int nr = cr + dr[k], nc = cc + dc[k];
                        if (nr < 0 || nr >= N || nc < l || nc > r) continue;
                        if (!active(nr, nc, m)) continue;
                        int ni = idx(nr, nc, m);
                        if (dist[ni] == INF) { dist[ni] = d + 1; q.push_back(ni); }
                    }
                    if (G[cr][cc] == '.') {          // spin
                        int ni = cur ^ 1;
                        if (dist[ni] == INF) { dist[ni] = d + 1; q.push_back(ni); }
                    }
                }
                D.push_back(move(dist));
            }
        }

        for (int id : here) {
            const Query &Qy = qs[id];
            long long best = INF;
            for (auto &ds : D) {
                long long a = ds[idx(Qy.rs, Qy.cs, 0)];
                if (a >= INF) continue;
                for (int em = 0; em < 2; em++) {
                    long long b = ds[idx(Qy.re, Qy.ce, em)];
                    if (b >= INF) continue;
                    best = min(best, a + b);
                }
            }
            ans[id] = (best <= Qy.K);
        }
    }

    solve(l, mid - 1, L);
    solve(mid + 1, r, R);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int q;
        scanf("%d %d %d", &N, &M, &q);
        G.assign(N, "");
        char buf[4105];
        for (int i = 0; i < N; i++) { scanf("%s", buf); G[i] = buf; }
        qs.assign(q, {});
        ans.assign(q, 0);
        vector<int> ids;
        for (int i = 0; i < q; i++) {
            scanf("%d %d %d %d %lld", &qs[i].rs, &qs[i].cs, &qs[i].re, &qs[i].ce, &qs[i].K);
            if (qs[i].rs == qs[i].re && qs[i].cs == qs[i].ce) ans[i] = 1;  // distance 0
            else ids.push_back(i);
        }
        solve(0, M - 1, ids);
        for (int i = 0; i < q; i++) puts(ans[i] ? "YES" : "NO");
    }
    return 0;
}