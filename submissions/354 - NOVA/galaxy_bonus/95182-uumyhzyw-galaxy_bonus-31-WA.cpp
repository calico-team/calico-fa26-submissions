#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < b; i++)
#define sz(x) (int)(x).size()

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    if (!(cin >> cases)) return 0;
    while (cases--) {
        int R, C, Q;
        cin >> R >> C >> Q;

        vector<string> board(R);
        rep(i, 0, R) cin >> board[i];

        auto check = [&](int r, int c, int m) {
            if (board[r][c] == '.') return true;
            return board[r][c] == 'B' ? (m == 0) : (m == 1);
        };

        vector<int> group(R * C * 2, -1);
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        int gid = 0;

        rep(i, 0, R * C * 2) {
            int r = (i / 2) / C;
            int c = (i / 2) % C;
            int m = i % 2;

            if (group[i] != -1 || !check(r, c, m)) continue;

            queue<int> pending;
            pending.push(i);
            group[i] = gid;

            while (!pending.empty()) {
                int curr = pending.front();
                pending.pop();

                int cr = (curr / 2) / C;
                int cc = (curr / 2) % C;
                int cm = curr % 2;

                int flipped = curr ^ 1;
                if (board[cr][cc] == '.' && group[flipped] == -1) {
                    group[flipped] = gid;
                    pending.push(flipped);
                }

                rep(d, 0, 4) {
                    int nr = cr + dx[d];
                    int nc = cc + dy[d];
                    if (nr < 0 || nr >= R || nc < 0 || nc >= C || !check(nr, nc, cm)) continue;
                    int nxt = (nr * C + nc) * 2 + cm;
                    if (group[nxt] == -1) {
                        group[nxt] = gid;
                        pending.push(nxt);
                    }
                }
            }
            gid++;
        }

        while (Q--) {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            int u = (r1 * C + c1) * 2;
            int v = (r2 * C + c2) * 2;
            if (group[u] != -1 && group[u] == group[v]) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    return 0;
}