#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> G(N);
        for (int i = 0; i < N; i++) cin >> G[i];

        struct Query { int sr, sc, er, ec; int K; };
        vector<Query> qs(Q);
        for (int i = 0; i < Q; i++) {
            cin >> qs[i].sr >> qs[i].sc >> qs[i].er >> qs[i].ec >> qs[i].K;
        }
        vector<string> ans(Q);

        auto id = [&](int r, int c, int mode) {
            return (r * M + c) * 2 + mode;
        };
        auto active = [&](int r, int c, int mode) -> bool {
            char ch = G[r][c];
            if (ch == '.') return true;
            if (ch == 'R') return mode == 1;
            if (ch == 'B') return mode == 0;
            return false;
        };

        // group by start
        map<pair<int,int>, vector<int>> groups;
        for (int i = 0; i < Q; i++) groups[{qs[i].sr, qs[i].sc}].push_back(i);

        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};
        int V = N * M * 2;
        vector<int> dist(V);
        vector<int> q;
        q.reserve(V);

        for (auto &gp : groups) {
            int sr = gp.first.first;
            int sc = gp.first.second;
            auto &idxs = gp.second;

            // destinations needed for this start
            // dest cell -> list of query idx (we need min dist per query, same cell same dist)
            unordered_map<int, vector<int>> need;
            need.reserve(idxs.size()*2);
            for (int qi : idxs) {
                int destCell = qs[qi].er * M + qs[qi].ec;
                need[destCell].push_back(qi);
            }
            int needCnt = (int)need.size();
            unordered_map<int,int> best; // destCell -> dist
            best.reserve(needCnt*2);

            fill(dist.begin(), dist.end(), -1);
            q.clear();
            int s = id(sr, sc, 0); // start in blue mode
            // start is normal per statement, so active
            dist[s] = 0;
            q.push_back(s);
            size_t head = 0;

            // start cell itself may be a destination
            int startCell = sr * M + sc;
            if (need.count(startCell)) {
                best[startCell] = 0;
            }

            while (head < q.size() && (int)best.size() < needCnt) {
                int cur = q[head++];
                int mode = cur % 2;
                int tmp = cur / 2;
                int r = tmp / M;
                int c = tmp % M;
                int d = dist[cur];

                // spin on normal tile
                if (G[r][c] == '.') {
                    int nid = id(r, c, mode ^ 1);
                    if (dist[nid] == -1) {
                        dist[nid] = d + 1;
                        q.push_back(nid);
                        int cell = r * M + c;
                        if (need.count(cell) && !best.count(cell)) best[cell] = d + 1;
                    }
                }
                // moves
                for (int dir = 0; dir < 4; dir++) {
                    int nr = r + dr[dir];
                    int nc = c + dc[dir];
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
                    if (!active(nr, nc, mode)) continue;
                    int nid = id(nr, nc, mode);
                    if (dist[nid] == -1) {
                        dist[nid] = d + 1;
                        q.push_back(nid);
                        int cell = nr * M + nc;
                        if (need.count(cell) && !best.count(cell)) best[cell] = d + 1;
                    }
                }
            }

            for (int qi : idxs) {
                int destCell = qs[qi].er * M + qs[qi].ec;
                auto it = best.find(destCell);
                if (it == best.end()) ans[qi] = "NO";
                else ans[qi] = (it->second <= qs[qi].K ? "YES" : "NO");
            }
        }

        for (int i = 0; i < Q; i++) cout << ans[i] << '\n';
    }
    return 0;
}