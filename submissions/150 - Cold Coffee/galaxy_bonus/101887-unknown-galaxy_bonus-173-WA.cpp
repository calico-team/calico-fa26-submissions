#include <bits/stdc++.h>

using namespace std;

/**
 * Return an array of Q strings, the i-th of which is "YES"
 * if Big Ben can travel from start[i] to end[i] within K[i]
 * seconds, and "NO" otherwise.
 *
 * N: the number of rows in the grid
 * M: the number of columns in the grid
 * Q: the number of queries
 * G: the grid, where each tile is 'R', 'B', or '.'
 * start: the (row, column) of the starting tile of each query
 * end: the (row, column) of the ending tile of each query
 * K: the maximum number of seconds allowed for each query
 */
vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end, vector<int>& K) {
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    auto ok = [&](int r, int c, int m) {
        char x = G[r][c];
        if (x == '.') return true;
        if (x == 'B') return m == 0;
        return m == 1;
    };
    auto enc = [&](int r, int c, int m) {
        return ((r * M + c) << 1) | m;
    };

    int INF = 1e9;
    vector<int> best(Q, INF);
    int V = N * M * 2;
    vector<int> d(V), mark(V, 0), q(V);
    int tm = 0;

    function<void(int, int, vector<int>&)> go = [&](int L, int R, vector<int>& qs) {
        if (qs.empty() || L > R) return;
        int mid = (L + R) / 2;

        for (int sr = 0; sr < N; sr++) for (int sm = 0; sm < 2; sm++) {
            if (!ok(sr, mid, sm)) continue;
            tm++;
            int h = 0, t = 0;
            int s0 = enc(sr, mid, sm);
            d[s0] = 0;
            mark[s0] = tm;
            q[t++] = s0;
            while (h < t) {
                int u = q[h++];
                int m = u & 1;
                int cell = u >> 1;
                int r = cell / M, c = cell % M;
                for (int k = 0; k < 4; k++) {
                    int nr = r + dx[k], nc = c + dy[k];
                    if (nr < 0 || nr >= N || nc < L || nc > R) continue;
                    if (!ok(nr, nc, m)) continue;
                    int v = enc(nr, nc, m);
                    if (mark[v] == tm) continue;
                    mark[v] = tm;
                    d[v] = d[u] + 1;
                    q[t++] = v;
                }
                if (G[r][c] == '.') {
                    int v = enc(r, c, m ^ 1);
                    if (mark[v] != tm) {
                        mark[v] = tm;
                        d[v] = d[u] + 1;
                        q[t++] = v;
                    }
                }
            }
            for (int qi : qs) {
                int sid = enc(start[qi].first, start[qi].second, 0);
                if (mark[sid] != tm) continue;
                int ds = d[sid];
                int er = end[qi].first, ec = end[qi].second;
                for (int m = 0; m < 2; m++) {
                    if (!ok(er, ec, m)) continue;
                    int tid = enc(er, ec, m);
                    if (mark[tid] != tm) continue;
                    best[qi] = min(best[qi], ds + d[tid]);
                }
            }
        }

        if (L == R) return;
        vector<int> Lq, Rq;
        for (int qi : qs) {
            int a = start[qi].second, b = end[qi].second;
            if (a < mid && b < mid) Lq.push_back(qi);
            else if (a > mid && b > mid) Rq.push_back(qi);
        }
        go(L, mid - 1, Lq);
        go(mid + 1, R, Rq);
    };

    vector<int> all(Q);
    iota(all.begin(), all.end(), 0);
    go(0, M - 1, all);

    vector<string> ans(Q);
    for (int i = 0; i < Q; i++) ans[i] = (best[i] <= K[i] ? "YES" : "NO");
    return ans;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> G(N);
        for (int j = 0; j < N; j++) {
            cin >> G[j];
        }
        vector<pair<int, int>> start, end;
        vector<int> K;
        for (int j = 0; j < Q; j++) {
            int start_row, start_col, end_row, end_col, k;
            cin >> start_row >> start_col >> end_row >> end_col >> k;
            start.push_back({start_row, start_col});
            end.push_back({end_row, end_col});
            K.push_back(k);
        }

        for (string s : solve(N, M, Q, G, start, end, K)) {
            cout << s << '\n';
        }
    }
}
