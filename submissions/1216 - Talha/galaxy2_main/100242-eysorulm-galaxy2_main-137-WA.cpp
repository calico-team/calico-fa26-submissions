#include <bits/stdc++.h>
using namespace std;

vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end, vector<int>& K) {
    int total_states = 2 * N * M;
    auto node_id = [&](int r, int c, int mode) {
        return (r * M + c) * 2 + mode;
    };

    unordered_map<int, vector<int>> dist_memo;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    auto get_dist = [&](int sr, int sc) -> const vector<int>& {
        int sid = sr * M + sc;
        if (dist_memo.count(sid)) return dist_memo[sid];

        vector<int>& dist = dist_memo[sid];
        dist.assign(total_states, -1);
        queue<int> q;
        int s = node_id(sr, sc, 0);
        dist[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            int um = u % 2;
            int ur = (u / 2) / M;
            int uc = (u / 2) % M;

            if (G[ur][uc] == '.') {
                int v = node_id(ur, uc, 1 - um);
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
            for (int d = 0; d < 4; d++) {
                int nr = ur + dr[d];
                int nc = uc + dc[d];
                if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                    if ((um == 0 && (G[nr][nc] == '.' || G[nr][nc] == 'B')) ||
                        (um == 1 && (G[nr][nc] == '.' || G[nr][nc] == 'R'))) {
                        int v = node_id(nr, nc, um);
                        if (dist[v] == -1) {
                            dist[v] = dist[u] + 1;
                            q.push(v);
                        }
                    }
                }
            }
        }
        return dist;
    };

    vector<string> ans(Q);
    for (int i = 0; i < Q; i++) {
        const auto& dist = get_dist(start[i].first, start[i].second);
        int er = end[i].first, ec = end[i].second;
        int best = 1e9;
        if (G[er][ec] == '.' || G[er][ec] == 'B') {
            int d = dist[node_id(er, ec, 0)];
            if (d != -1) best = min(best, d);
        }
        if (G[er][ec] == '.' || G[er][ec] == 'R') {
            int d = dist[node_id(er, ec, 1)];
            if (d != -1) best = min(best, d);
        }
        ans[i] = (best <= K[i]) ? "YES" : "NO";
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
        vector<pair<int, int>> start, end;
        vector<int> K;
        for (int j = 0; j < Q; j++) {
            int sr, sc, er, ec, k;
            cin >> sr >> sc >> er >> ec >> k;
            start.push_back({sr, sc});
            end.push_back({er, ec});
            K.push_back(k);
        }
        for (string s : solve(N, M, Q, G, start, end, K)) cout << s << '\n';
    }
}