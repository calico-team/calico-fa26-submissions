#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Query {
    int id;
    int sr, sc;
    int er, ec;
    int k;
};

void dnc(int L, int R, const vector<Query>& queries, int N, int M, const vector<string>& G, vector<int>& best_dist) {
    if (L > R || queries.empty()) return;
    int mid = L + (R - L) / 2;

    int W = R - L + 1;
    auto get_id = [&](int r, int c, int m) {
        return ((c - L) * N + r) * 2 + m;
    };
    int total_nodes = W * N * 2;

    vector<int> mid_nodes;
    for (int r = 0; r < N; r++) {
        for (int m = 0; m < 2; m++) {
            if (m == 0 && G[r][mid] != 'R') mid_nodes.push_back(get_id(r, mid, m));
            else if (m == 1 && G[r][mid] != 'B') mid_nodes.push_back(get_id(r, mid, m));
        }
    }

    int S = mid_nodes.size();
    vector<vector<int>> dist(S, vector<int>(total_nodes, -1));

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int s = 0; s < S; s++) {
        int src = mid_nodes[s];
        dist[s][src] = 0;
        queue<int> q;
        q.push(src);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            int d = dist[s][u];
            int m = u % 2;
            int r = (u / 2) % N;
            int c = L + (u / 2) / N;

            // Spin
            if (G[r][c] == '.') {
                int v = get_id(r, c, 1 - m);
                if (dist[s][v] == -1) {
                    dist[s][v] = d + 1;
                    q.push(v);
                }
            }

            // Walk
            for (int dir = 0; dir < 4; dir++) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];
                if (nr >= 0 && nr < N && nc >= L && nc <= R) {
                    if (m == 0 && G[nr][nc] != 'R') {
                        int v = get_id(nr, nc, 0);
                        if (dist[s][v] == -1) {
                            dist[s][v] = d + 1;
                            q.push(v);
                        }
                    } else if (m == 1 && G[nr][nc] != 'B') {
                        int v = get_id(nr, nc, 1);
                        if (dist[s][v] == -1) {
                            dist[s][v] = d + 1;
                            q.push(v);
                        }
                    }
                }
            }
        }
    }

    vector<Query> left_q, right_q;
    for (const auto& qry : queries) {
        int start_node = get_id(qry.sr, qry.sc, 0);
        int end_nodes[2];
        int end_cnt = 0;
        if (G[qry.er][qry.ec] != 'R') end_nodes[end_cnt++] = get_id(qry.er, qry.ec, 0);
        if (G[qry.er][qry.ec] != 'B') end_nodes[end_cnt++] = get_id(qry.er, qry.ec, 1);

        for (int s = 0; s < S; s++) {
            int d1 = dist[s][start_node];
            if (d1 == -1) continue;
            for (int e = 0; e < end_cnt; e++) {
                int d2 = dist[s][end_nodes[e]];
                if (d2 != -1) {
                    best_dist[qry.id] = min(best_dist[qry.id], d1 + d2);
                }
            }
        }

        int c_min = min(qry.sc, qry.ec);
        int c_max = max(qry.sc, qry.ec);
        if (c_max < mid) left_q.push_back(qry);
        else if (c_min > mid) right_q.push_back(qry);
    }

    dnc(L, mid - 1, left_q, N, M, G, best_dist);
    dnc(mid + 1, R, right_q, N, M, G, best_dist);
}

vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end, vector<int>& K) {
    vector<Query> queries(Q);
    vector<int> best_dist(Q, INF);
    for (int i = 0; i < Q; i++) {
        queries[i] = {i, start[i].first, start[i].second, end[i].first, end[i].second, K[i]};
    }

    dnc(0, M - 1, queries, N, M, G, best_dist);

    vector<string> ans(Q);
    for (int i = 0; i < Q; i++) {
        ans[i] = (best_dist[i] <= K[i]) ? "YES" : "NO";
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
        vector<int> K(Q);
        for (int j = 0; j < Q; j++) {
            cin >> start[j].first >> start[j].second >> end[j].first >> end[j].second >> K[j];
        }
        for (const string& s : solve(N, M, Q, G, start, end, K)) {
            cout << s << '\n';
        }
    }
    return 0;
}