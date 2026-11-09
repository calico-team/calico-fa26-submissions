#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> grid(N);
        for (int i = 0; i < N; i++)
            cin >> grid[i];

        vector<bool> visited(2 * N * M, false);

        auto id = [&](int r, int c, int mode) {
            return (r * M + c) * 2 + mode;
        };

        auto valid = [&](int r, int c, int mode) {
            if (r < 0 || r >= N || c < 0 || c >= M)
                return false;

            char tile = grid[r][c];

            return tile == '.' ||
                   (tile == 'B' && mode == 0) ||
                   (tile == 'R' && mode == 1);
        };

        queue<tuple<int, int, int>> q;

        int er = N - 1, ec = M - 1;

        for (int mode = 0; mode < 2; mode++) {
            if (valid(er, ec, mode)) {
                visited[id(er, ec, mode)] = true;
                q.push({er, ec, mode});
            }
        }

        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        while (!q.empty()) {
            auto [r, c, mode] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (!valid(nr, nc, mode))
                    continue;

                int next = id(nr, nc, mode);

                if (!visited[next]) {
                    visited[next] = true;
                    q.push({nr, nc, mode});
                }
            }

            if (grid[r][c] == '.') {
                int nm = 1 - mode;
                int next = id(r, c, nm);

                if (!visited[next]) {
                    visited[next] = true;
                    q.push({r, c, nm});
                }
            }
        }

        while (Q--) {
            int sr, sc, er, ec;
            cin >> sr >> sc >> er >> ec;

            cout << (visited[id(sr, sc, 0)]
                     ? "YES\n" : "NO\n");
        }
    }
}