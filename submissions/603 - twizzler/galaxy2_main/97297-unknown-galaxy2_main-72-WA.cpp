#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 10;
const int MAXM = 4000;
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

int dist[MAXN][MAXM][2];
int vis[MAXN][MAXM][2];
int timer = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> G(N);
        for (int i = 0; i < N; i++) cin >> G[i];

        vector<array<int, 5>> queries(Q);
        vector<pair<pair<int, int>, int>> starts;
        for (int i = 0; i < Q; i++) {
            int rs, cs, re, ce, k;
            cin >> rs >> cs >> re >> ce >> k;
            queries[i] = {rs, cs, re, ce, k};
            starts.emplace_back(make_pair(rs, cs), i);
        }
        sort(starts.begin(), starts.end());

        vector<string> ans(Q, "NO");

        for (int s = 0; s < (int)starts.size(); ) {
            int sr = starts[s].first.first;
            int sc = starts[s].first.second;
            int e = s;
            while (e < (int)starts.size() && starts[e].first == starts[s].first) e++;

            ++timer;
            if (timer > 1e9) {
                memset(vis, 0, sizeof(vis));
                timer = 1;
            }

            queue<tuple<int, int, int>> q;
            dist[sr][sc][0] = 0;
            vis[sr][sc][0] = timer;
            q.emplace(sr, sc, 0);

            while (!q.empty()) {
                auto [r, c, mode] = q.front();
                q.pop();
                int d = dist[r][c][mode];

                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;

                    char tile = G[nr][nc];
                    bool can_stand = (tile == '.') || (mode == 0 && tile == 'B') || (mode == 1 && tile == 'R');
                    if (can_stand && vis[nr][nc][mode] != timer) {
                        vis[nr][nc][mode] = timer;
                        dist[nr][nc][mode] = d + 1;
                        q.emplace(nr, nc, mode);
                    }
                }

                if (G[r][c] == '.' && vis[r][c][1 - mode] != timer) {
                    vis[r][c][1 - mode] = timer;
                    dist[r][c][1 - mode] = d + 1;
                    q.emplace(r, c, 1 - mode);
                }
            }

            for (int i = s; i < e; i++) {
                int id = starts[i].second;
                int re = queries[id][2];
                int ce = queries[id][3];
                int K = queries[id][4];
                int best = INF;
                if (vis[re][ce][0] == timer) best = min(best, dist[re][ce][0]);
                if (vis[re][ce][1] == timer) best = min(best, dist[re][ce][1]);
                if (best <= K) ans[id] = "YES";
            }
            s = e;
        }

        for (auto& x : ans) cout << x << '\n';
    }
    return 0;
}
