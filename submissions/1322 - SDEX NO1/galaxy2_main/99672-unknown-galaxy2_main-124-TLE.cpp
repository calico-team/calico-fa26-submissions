#include <bits/stdc++.h>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const long long INF = 1000000000000000000LL;

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
    for (int t = 0; t < T; t++) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> g(N);
        for (int i = 0; i < N; i++) {
            cin >> g[i];
        }

        vector<vector<vector<bool> > > can(N, vector<vector<bool> >(M, vector<bool>(2)));
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                char ch = g[r][c];
                if (ch == '.' || ch == 'B') {
                    can[r][c][0] = true;
                } else {
                    can[r][c][0] = false;
                }
                if (ch == '.' || ch == 'R') {
                    can[r][c][1] = true;
                } else {
                    can[r][c][1] = false;
                }
            }
        }

        vector<vector<vector<Query> > > queries(N, vector<vector<Query> >(M));
        vector<string> ans(Q);
        vector<pair<int, int> > start_list;
        vector<vector<char> > vis_start(N, vector<char>(M, 0));

        for (int qid = 0; qid < Q; qid++) {
            int sr, sc, er, ec;
            long long K;
            cin >> sr >> sc >> er >> ec >> K;
            if (sr == er && sc == ec) {
                ans[qid] = "YES";
                continue;
            }
            Query qtmp;
            qtmp.er = er;
            qtmp.ec = ec;
            qtmp.idx = qid;
            qtmp.K = K;
            queries[sr][sc].push_back(qtmp);
            if (vis_start[sr][sc] == 0) {
                vis_start[sr][sc] = 1;
                start_list.push_back(make_pair(sr, sc));
            }
        }

        int total = 2 * N * M;
        vector<long long> dist(total, INF);
        vector<int> touched;
        touched.reserve(total);

        for (int si = 0; si < (int)start_list.size(); si++) {
            int sr = start_list[si].first;
            int sc = start_list[si].second;

            vector<int> q;
            q.reserve(total);
            int ql = 0;

            int st_id = get_id(sr, sc, 0, M);
            dist[st_id] = 0;
            q.push_back(st_id);
            touched.push_back(st_id);

            while (ql < (int)q.size()) {
                int u = q[ql];
                ql++;

                int pos = u / 2;
                int s = u % 2;
                int r = pos / M;
                int c = pos % M;
                long long d = dist[u];

                for (int dir = 0; dir < 4; dir++) {
                    int nr = r + dx[dir];
                    int nc = c + dy[dir];
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) {
                        continue;
                    }
                    if (can[nr][nc][s] == false) {
                        continue;
                    }
                    int v = get_id(nr, nc, s, M);
                    if (dist[v] > d + 1) {
                        dist[v] = d + 1;
                        q.push_back(v);
                        touched.push_back(v);
                    }
                }

                if (g[r][c] == '.') {
                    int ns = s ^ 1;
                    int v = get_id(r, c, ns, M);
                    if (dist[v] > d + 1) {
                        dist[v] = d + 1;
                        q.push_back(v);
                        touched.push_back(v);
                    }
                }
            }

            for (int i = 0; i < (int)queries[sr][sc].size(); i++) {
                Query qq = queries[sr][sc][i];
                int eid0 = get_id(qq.er, qq.ec, 0, M);
                int eid1 = get_id(qq.er, qq.ec, 1, M);
                long long d0 = dist[eid0];
                long long d1 = dist[eid1];
                long long best;
                if (d0 < d1) {
                    best = d0;
                } else {
                    best = d1;
                }
                if (best <= qq.K) {
                    ans[qq.idx] = "YES";
                } else {
                    ans[qq.idx] = "NO";
                }
            }

            for (int i = 0; i < (int)touched.size(); i++) {
                int x = touched[i];
                dist[x] = INF;
            }
            touched.clear();
        }

        string out;
        out.reserve(Q * 5);
        for (int i = 0; i < Q; i++) {
            out += ans[i];
            out += '\n';
        }
        cout << out;
    }
    return 0;
}

