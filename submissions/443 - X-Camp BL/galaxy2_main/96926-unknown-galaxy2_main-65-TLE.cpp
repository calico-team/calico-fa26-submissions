#include <bits/stdc++.h>
using namespace std;
int dc[] = {0, 0, -1, 1};
int dr[] = {-1, 1, 0, 0};
struct qq {
    int sr, sc, er, ec, K, id;
};
struct State {
    int r, c, m;
};
int N, M, Q;
vector<string> G;
const int INF = 1e9 + 7;
vector<int> ans_val;
void diss(int mid_col, vector<vector<vector<vector<int>>>>& dists) {
    dists.assign(N, vector<vector<vector<int>>>(2, vector<vector<int>>(N, vector<int>(M, INF))));
    for (int rst = 0; rst < N; ++rst) {
        for (int mst = 0; mst < 2; ++mst) {
            char start_tile = G[rst][mid_col];
            if (start_tile == 'R' && mst == 0) continue;
            if (start_tile == 'B' && mst == 1) continue;
            auto& d = dists[rst][mst];
            d[rst][mid_col] = 0;
            queue<State> q;
            q.push({rst, mid_col, mst});
            while (!q.empty()) {
                State curr = q.front();
                q.pop();
                int r = curr.r;
                int c = curr.c;
                int m = curr.m;
                int cur_d = d[r][c];
                if (G[r][c] == '.') {
                    int next_m = 1 - m;
                    char next_tile = G[r][c];
                    if (d[r][c] > cur_d + 1) {
                        
                    }
                }
            }
        }
    }
}
void solve() {
    if (!(cin >> N >> M >> Q)) return;
    G.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> G[i];
    }
    vector<qq> qqs(Q);
    ans_val.assign(Q, INF);
    for (int i = 0; i < Q; ++i) {
        cin >> qqs[i].sr >> qqs[i].sc >> qqs[i].er >> qqs[i].ec >> qqs[i].K;
        qqs[i].id = i;
    }
    vector<vector<vector<int>>> dst(N, vector<vector<int>>(M, vector<int>(2, INF))); 
    struct fsd {
        int r, c, m;
    };   
    vector<vector<vector<vector<int>>>> dist_from(N, vector<vector<vector<int>>>(M, vector<vector<int>>(2)));
    for (int qi = 0; qi < Q; ++qi) {
        int sr = qqs[qi].sr;
        int sc = qqs[qi].sc;
        int er = qqs[qi].er;
        int ec = qqs[qi].ec;
        int K = qqs[qi].K;
        vector<vector<vector<int>>> dist(N, vector<vector<int>>(M, vector<int>(2, INF)));
        queue<fsd> q;
        dist[sr][sc][0] = 0;
        q.push({sr, sc, 0});
        while (!q.empty()) {
            fsd curr = q.front();
            q.pop();
            int r = curr.r; int c = curr.c; int m = curr.m;
            int d = dist[r][c][m];
            if (r == er && c == ec) {
                ans_val[qi] = d;
                break;
            }
            if (G[r][c] == '.') {
                if (dist[r][c][1 - m] > d + 1) {
                    dist[r][c][1 - m] = d + 1;
                    q.push({r, c, 1 - m});
                }
            }
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i]; 
                if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                    char tile = G[nr][nc];
                    if (tile == '.' || (m == 0 && tile == 'B') || (m == 1 && tile == 'R')) {
                        if (dist[nr][nc][m] > d + 1) {
                            dist[nr][nc][m] = d + 1;
                            q.push({nr, nc, m});
                        }
                    }
                }
            }
        }
        if (ans_val[qi] <= K) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) solve();
    }
}
