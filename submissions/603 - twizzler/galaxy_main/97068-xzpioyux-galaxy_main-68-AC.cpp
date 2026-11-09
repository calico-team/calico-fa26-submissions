#include <bits/stdc++.h>
using namespace std;

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

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

        auto valid = [&](int r, int c, int mode) {
            if (r < 0 || r >= N || c < 0 || c >= M) return false;
            char t = G[r][c];
            if (t == '.') return true;
            if (mode == 0) return t == 'B';
            return t == 'R';
        };

        vector<vector<array<int, 2>>> comp(N, vector<array<int, 2>>(M, {-1, -1}));
        int cid = 0;
        queue<tuple<int, int, int>> q;

        for (int sr = 0; sr < N; sr++) {
            for (int sc = 0; sc < M; sc++) {
                for (int sm = 0; sm < 2; sm++) {
                    if (!valid(sr, sc, sm) || comp[sr][sc][sm] != -1) continue;

                    comp[sr][sc][sm] = cid;
                    q.emplace(sr, sc, sm);

                    while (!q.empty()) {
                        auto [r, c, mode] = q.front();
                        q.pop();

                        for (int k = 0; k < 4; k++) {
                            int nr = r + dr[k];
                            int nc = c + dc[k];
                            if (valid(nr, nc, mode) && comp[nr][nc][mode] == -1) {
                                comp[nr][nc][mode] = cid;
                                q.emplace(nr, nc, mode);
                            }
                        }

                        if (G[r][c] == '.' && comp[r][c][1 - mode] == -1) {
                            comp[r][c][1 - mode] = cid;
                            q.emplace(r, c, 1 - mode);
                        }
                    }
                    cid++;
                }
            }
        }

        for (int i = 0; i < Q; i++) {
            int rs, cs, re, ce;
            cin >> rs >> cs >> re >> ce;

            int start_c = comp[rs][cs][0];
            bool ok = false;
            if (valid(re, ce, 0) && comp[re][ce][0] == start_c) ok = true;
            if (valid(re, ce, 1) && comp[re][ce][1] == start_c) ok = true;

            cout << (ok ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}
