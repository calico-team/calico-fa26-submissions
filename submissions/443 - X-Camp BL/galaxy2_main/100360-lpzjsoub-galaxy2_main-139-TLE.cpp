#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9 + 7;
int dc[] = {0, 0, -1, 1};
int dr[] = {-1, 1, 0, 0};
void solve() {
    int N, M, Q;
    if (!(cin >> N >> M >> Q)) return;
    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
    }
    vector<vector<vector<int>>> dist(N, vector<vector<int>>(M, vector<int>(2, INF)));
    deque<pair<pair<int, int>, int>> dq;
    for (int i = 0; i < Q; ++i) {
        int rst, cst, rd, cd, K;
        cin >> rst >> cst >> rd >> cd >> K;
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                dist[r][c][0] = INF;
                dist[r][c][1] = INF;
            }
        }
        dist[rst][cst][0] = 0;
        dq.push_back({{rst, cst}, 0});
        while (!dq.empty()) {
            auto curr = dq.front();
            dq.pop_front();
            int r = curr.first.first;
            int c = curr.first.second;
            int mode = curr.second;
            int d = dist[r][c][mode];
            if (grid[r][c] == '.') {
                int next_mode = 1 - mode;
                if (d + 1 < dist[r][c][next_mode]) {
                    dist[r][c][next_mode] = d + 1;
                    dq.push_back({{r, c}, next_mode});
                }
            }
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                    char tile = grid[nr][nc];
                    bool ww = (tile == '.') || (mode == 0 && tile == 'B') || (mode == 1 && tile == 'R');
                    if (ww && d + 1 < dist[nr][nc][mode]) {
                        dist[nr][nc][mode] = d + 1;
                        dq.push_back({{nr, nc}, mode});
                    }
                }
            }
        }
        int mdis = min(dist[rd][cd][0], dist[rd][cd][1]);
        if (mdis <= K) {
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