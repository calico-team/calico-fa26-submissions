#include <bits/stdc++.h>
using namespace std;

vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {
    int total_states = 2 * N * M;
    auto node_id = [&](int r, int c, int mode) {
        return (r * M + c) * 2 + mode;
    };

    vector<int> comp(total_states, -1);
    int current_comp = 0;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < total_states; i++) {
        if (comp[i] != -1) continue;
        int m = i % 2;
        int idx = i / 2;
        int r = idx / M;
        int c = idx % M;
        if (G[r][c] == 'R' && m == 0) continue;
        if (G[r][c] == 'B' && m == 1) continue;

        queue<int> q;
        q.push(i);
        comp[i] = current_comp;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            int um = u % 2;
            int ur = (u / 2) / M;
            int uc = (u / 2) % M;

            if (G[ur][uc] == '.') {
                int v = node_id(ur, uc, 1 - um);
                if (comp[v] == -1) {
                    comp[v] = current_comp;
                    q.push(v);
                }
            }

            for (int d = 0; d < 4; d++) {
                int nr = ur + dr[d];
                int nc = uc + dc[d];
                if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                    if (um == 0 && (G[nr][nc] == '.' || G[nr][nc] == 'B')) {
                        int v = node_id(nr, nc, 0);
                        if (comp[v] == -1) {
                            comp[v] = current_comp;
                            q.push(v);
                        }
                    } else if (um == 1 && (G[nr][nc] == '.' || G[nr][nc] == 'R')) {
                        int v = node_id(nr, nc, 1);
                        if (comp[v] == -1) {
                            comp[v] = current_comp;
                            q.push(v);
                        }
                    }
                }
            }
        }
        current_comp++;
    }

    vector<string> ans(Q);
    for (int i = 0; i < Q; i++) {
        int s = node_id(start[i].first, start[i].second, 0);
        int er = end[i].first, ec = end[i].second;
        bool ok = false;
        if (G[er][ec] == '.' || G[er][ec] == 'B') {
            int e0 = node_id(er, ec, 0);
            if (comp[s] != -1 && comp[s] == comp[e0]) ok = true;
        }
        if (G[er][ec] == '.' || G[er][ec] == 'R') {
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
    int T; if (!(cin >> T)) return 0;
    while (T--) {
        int N, M, Q; cin >> N >> M >> Q;
        vector<string> G(N);
        for (int j = 0; j < N; j++) cin >> G[j];
        vector<pair<int, int>> start(Q), end(Q);
        for (int j = 0; j < Q; j++) cin >> start[j].first >> start[j].second >> end[j].first >> end[j].second;
        for (string s : solve(N, M, Q, G, start, end)) cout << s << '\n';
    }
}