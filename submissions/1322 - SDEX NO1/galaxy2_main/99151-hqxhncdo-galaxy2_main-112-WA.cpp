#include <bits/stdc++.h>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const int INF = 1e9;
struct Query {
    int er, ec, idx;
    long long K;
};

inline int get_id(int r, int c, int s, int M) {
    return 2 * (r * M + c) + s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie();

    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> g(N);
        for (int i = 0; i < N; ++i) {
            cin >> g[i];
        }

        vector< vector< vector<Query> > > queries(N, vector< vector<Query> >(M));
        vector<string> ans(Q);

        for (int qid = 0; qid < Q; ++qid) {
            int sr, sc, er, ec;
            long long K;
            cin >> sr >> sc >> er >> ec >> K;
            queries[sr][sc].push_back({er, ec, qid, K});
        }

        for (int sr = 0; sr < N; ++sr) {
            for (int sc = 0; sc < M; ++sc) {
                if (queries[sr][sc].empty()) continue;

                int total_nodes = 2 * N * M;
                vector<int> dist(total_nodes, INF);
                queue<int> q;

                int start_id = get_id(sr, sc, 0, M);
                dist[start_id] = 0;
                q.push(start_id);

                while (!q.empty()) {
                    int u = q.front();
                    q.pop();

                    int pos = u / 2;
                    int s = u % 2;
                    int r = pos / M;
                    int c = pos % M;
                    int d = dist[u];

                    for (int dir = 0; dir < 4; ++dir) {
                        int nr = r + dx[dir];
                        int nc = c + dy[dir];
                        if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
                        char ch = g[nr][nc];
                        bool ok = false;
                        if (s == 0) {
                            if (ch == '.' || ch == 'B') ok = true;
                        } else {
                            if (ch == '.' || ch == 'R') ok = true;
                        }
                        if (!ok) continue;
                        int v = get_id(nr, nc, s, M);
                        if (dist[v] > d + 1) {
                            dist[v] = d + 1;
                            q.push(v);
                        }
                    }

                    if (g[r][c] == '.') {
                        int ns = s ^ 1;
                        int v = get_id(r, c, ns, M);
                        if (dist[v] > d + 1) {
                            dist[v] = d + 1;
                            q.push(v);
                        }
                    }
                }
                for (int i = 0; i < queries[sr][sc].size(); ++i) {
                    Query qq = queries[sr][sc][i];
                    int er = qq.er;
                    int ec = qq.ec;
                    int qidx = qq.idx;
                    long long K = qq.K;

                    int d0 = dist[get_id(er, ec, 0, M)];
                    int d1 = dist[get_id(er, ec, 1, M)];
                    int best = min(d0, d1);
                    if (best <= K) {
                        ans[qidx] = "YES";
                    } else {
                        ans[qidx] = "NO";
                    }
                }
            }
        }

        for (int i = 0; i < ans.size(); ++i) {
            string s = ans[i];
            cout << s << '\n';
        }
    }
    return 0;
}

