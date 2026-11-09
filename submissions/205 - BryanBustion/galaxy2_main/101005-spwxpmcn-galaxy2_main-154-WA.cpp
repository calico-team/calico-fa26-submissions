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
    const int INF = 1e9;
    const int V = N * M * 2;
    auto id = [&](int r, int c, int mode) {
        return (c * N + r) * 2 + mode;
    };
    auto valid = [&](int r, int c, int mode) {
        if (r < 0 || r >= N || c < 0 || c >= M)
            return false;
        return G[r][c] == '.' ||
               (G[r][c] == 'B' && mode == 0) ||
               (G[r][c] == 'R' && mode == 1);
    };
    vector<vector<pair<int,int>>> adj(V);
    const int dr[] = {-1, 1, 0, 0};
    const int dc[] = {0, 0, -1, 1};
    for (int c = 0; c < M; c++) {
        for (int r = 0; r < N; r++) {
            for (int mode = 0; mode < 2; mode++) {
                if (!valid(r, c, mode))
                    continue;
                int u = id(r, c, mode);
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    if (valid(nr, nc, mode)) {
                        int v = id(nr, nc, mode);
                        adj[u].push_back({v, 1});
                    }
                }
                if (G[r][c] == '.') {
                    int v = id(r, c, mode ^ 1);
                    adj[u].push_back({v, 1});
                }
            }
        }
    }
    vector<vector<int>> groups(V);
    for (int i = 0; i < Q; i++) {
        int s = id(start[i].first, start[i].second, 0);
        groups[s].push_back(i);
    }
    vector<string> ans(Q, "NO");
    vector<int> dist(V);
    for (int s = 0; s < V; s++) {
        if (groups[s].empty())
            continue;
        fill(dist.begin(), dist.end(), INF);
        queue<int> qu;
        dist[s] = 0;
        qu.push(s);
        while (!qu.empty()) {
            int u = qu.front();
            qu.pop();
            for (auto [v, w] : adj[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    qu.push(v);
                }
            }
        }
        for (int qi : groups[s]) {
            int er = end[qi].first;
            int ec = end[qi].second;
            int best = INF;
            for (int mode = 0; mode < 2; mode++) {
                if (valid(er, ec, mode)) {
                    best = min(best, dist[id(er, ec, mode)]);
                }
            }
            if (best <= K[qi])
                ans[qi] = "YES";
        }
    }
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