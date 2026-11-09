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
    // The state graph is (cell, mode); all moves (walk / spin) cost 1 and are reversible,
    // so distances are symmetric. N <= 10, so use divide & conquer on columns: for a
    // column range [l, r] with middle column m, BFS from every state in column m
    // (restricted to [l, r]). Any shortest path inside [l, r] either touches column m
    // (answered by min over s of d(start,s) + d(s,end)) or lies fully in one half.
    const int INF = 1e9;
    auto active = [&](int r, int c, int mode) {
        char ch = G[r][c];
        return ch == '.' || (ch == 'B' && mode == 0) || (ch == 'R' && mode == 1);
    };
    vector<long long> best(Q, (long long)INF * 4);
    vector<vector<int>> dist;
    vector<int> q;

    function<void(int, int, vector<int>&)> rec = [&](int l, int r, vector<int>& qs) {
        if (qs.empty() || l > r) return;
        int mid = (l + r) / 2, len = r - l + 1;
        int S = N * len * 2;
        auto id = [&](int row, int c, int mode) { return ((row * len) + (c - l)) * 2 + mode; };
        vector<int> sources;
        for (int row = 0; row < N; row++)
            for (int mode = 0; mode < 2; mode++)
                if (active(row, mid, mode)) sources.push_back(id(row, mid, mode));
        int ns = sources.size();
        dist.assign(ns, vector<int>(S, INF));
        const int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
        for (int si = 0; si < ns; si++) {
            vector<int>& d = dist[si];
            q.assign(1, sources[si]);
            d[sources[si]] = 0;
            for (size_t h = 0; h < q.size(); h++) {
                int u = q[h];
                int mode = u & 1, cell = u >> 1, c = l + cell % len, row = cell / len;
                if (G[row][c] == '.') {
                    int v = u ^ 1;
                    if (d[v] == INF) { d[v] = d[u] + 1; q.push_back(v); }
                }
                for (int k = 0; k < 4; k++) {
                    int nr = row + dr[k], nc = c + dc[k];
                    if (nr < 0 || nr >= N || nc < l || nc > r || !active(nr, nc, mode)) continue;
                    int v = id(nr, nc, mode);
                    if (d[v] == INF) { d[v] = d[u] + 1; q.push_back(v); }
                }
            }
        }
        vector<int> left, right;
        for (int qi : qs) {
            int sr = start[qi].first, sc = start[qi].second;
            int er = end[qi].first, ec = end[qi].second;
            int a = id(sr, sc, 0);
            int e0 = active(er, ec, 0) ? id(er, ec, 0) : -1;
            int e1 = active(er, ec, 1) ? id(er, ec, 1) : -1;
            for (int si = 0; si < ns; si++) {
                int da = dist[si][a];
                if (da >= INF) continue;
                int db = INF;
                if (e0 >= 0) db = min(db, dist[si][e0]);
                if (e1 >= 0) db = min(db, dist[si][e1]);
                if (db < INF) best[qi] = min(best[qi], (long long)da + db);
            }
            if (sc < mid && ec < mid) left.push_back(qi);
            else if (sc > mid && ec > mid) right.push_back(qi);
        }
        rec(l, mid - 1, left);
        rec(mid + 1, r, right);
    };
    vector<int> all(Q);
    iota(all.begin(), all.end(), 0);
    rec(0, M - 1, all);
    vector<string> ans(Q);
    for (int i = 0; i < Q; i++) ans[i] = best[i] <= K[i] ? "YES" : "NO";
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
