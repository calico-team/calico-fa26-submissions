#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct st {
    int r, c, m;
};
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
void solve() {
    int N, M, Q;
    if (!(cin >> N >> M >> Q)) return;
    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
    }
    vector<vector<vector<int>>> comp(N, vector<vector<int>>(M, vector<int>(2, -1)));
    int cid = 0;
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            for (int m = 0; m < 2; ++m) {
                if (comp[r][c][m] != -1) continue;
                if (m == 0 && grid[r][c] == 'R') continue;
                if (m == 1 && grid[r][c] == 'B') continue;
                queue<st> q;
                comp[r][c][m] = cid;
                q.push({r, c, m});
                while (!q.empty()) {
                    st u = q.front();
                    q.pop();
                    if (grid[u.r][u.c] == '.') {
                        int nm = 1 - u.m;
                        if (comp[u.r][u.c][nm] == -1) {
                            comp[u.r][u.c][nm] = cid;
                            q.push({u.r, u.c, nm});
                        }
                    }
                    for (int i = 0; i < 4; ++i) {
                        int nr = u.r + dr[i];
                        int nc = u.c + dc[i];
                        if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                            if (u.m == 0 && grid[nr][nc] == 'R') continue;
                            if (u.m == 1 && grid[nr][nc] == 'B') continue;

                            if (comp[nr][nc][u.m] == -1) {
                                comp[nr][nc][u.m] = cid;
                                q.push({nr, nc, u.m});
                            }
                        }
                    }
                }
                cid++;
            }
        }
    }
    for (int i = 0; i < Q; i++) {
        int sr, sc, er, ec; cin >> sr >> sc >> er >> ec;
        int stc = comp[sr][sc][0];
        if (stc == -1) {
            cout << "NO" << endl;
            continue;
        }
        bool pos = false;
        if (grid[er][ec] == '.' || grid[er][ec] == 'B') {
            if (comp[er][ec][0] == stc) pos = true;
        }
        if (grid[er][ec] == '.' || grid[er][ec] == 'R') {
            if (comp[er][ec][1] == stc) pos = true;
        }
        if (pos) {
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