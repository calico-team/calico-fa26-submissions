#include <bits/stdc++.h>
using namespace std;

vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {
    auto node_id = [&](int r, int c, int m) {
        return (r * M + c) * 2 + m;
    };

    int total_nodes = 2 * N * M;
    vector<int> comp(total_nodes, -1);
    int comp_cnt = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // BFS to find connected components of valid (r, c, mode) states
    for (int i = 0; i < total_nodes; i++) {
        if (comp[i] != -1) continue;
        int r = (i / 2) / M;
        int c = (i / 2) % M;
        int m = i % 2;

        // Skip invalid states (R tiles in blue mode, B tiles in red mode)
        if (m == 0 && G[r][c] == 'R') continue;
        if (m == 1 && G[r][c] == 'B') continue;

        queue<int> q;
        comp[i] = comp_cnt;
        q.push(i);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            int ur = (u / 2) / M;
            int uc = (u / 2) % M;
            int um = u % 2;

            // Spin action: only possible on normal '.' tiles
            if (G[ur][uc] == '.') {
                int v = node_id(ur, uc, 1 - um);
                if (comp[v] == -1) {
                    comp[v] = comp_cnt;
                    q.push(v);
                }
            }

            // Move action: step to an adjacent tile active in current mode
            for (int d = 0; d < 4; d++) {
                int nr = ur + dr[d];
                int nc = uc + dc[d];
                if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                    if (um == 0 && G[nr][nc] != 'R') {
                        int v = node_id(nr, nc, 0);
                        if (comp[v] == -1) {
                            comp[v] = comp_cnt;
                            q.push(v);
                        }
                    } else if (um == 1 && G[nr][nc] != 'B') {
                        int v = node_id(nr, nc, 1);
                        if (comp[v] == -1) {
                            comp[v] = comp_cnt;
                            q.push(v);
                        }
                    }
                }
            }
        }
        comp_cnt++;
    }

    // Process all Q queries
    vector<string> ans(Q);
    for (int i = 0; i < Q; i++) {
        int s = node_id(start[i].first, start[i].second, 0);
        int er = end[i].first, ec = end[i].second;
        bool ok = false;

        // Can end in Blue mode if tile is not 'R'
        if (G[er][ec] != 'R') {
            int e0 = node_id(er, ec, 0);
            if (comp[s] != -1 && comp[s] == comp[e0]) ok = true;
        }
        // Can end in Red mode if tile is not 'B'
        if (G[er][ec] != 'B') {
            int e1 = node_id(er, ec, 1);
            if (comp[s] != -1 && comp[s] == comp[e1]) ok = true;
        }

        ans[i] = ok ? "YES" : "NO";
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> G(N);
        for (int j = 0; j < N; j++) cin >> G[j];
        vector<pair<int, int>> start(Q), end(Q);
        for (int j = 0; j < Q; j++) {
            cin >> start[j].first >> start[j].second >> end[j].first >> end[j].second;
        }
        for (const string& s : solve(N, M, Q, G, start, end)) {
            cout << s << '\n';
        }
    }
    return 0;
}