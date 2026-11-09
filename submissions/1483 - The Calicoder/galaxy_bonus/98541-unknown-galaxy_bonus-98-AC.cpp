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

        for (int i = 0; i < N; i++) {
            cin >> grid[i];
        }

        vector<vector<array<int, 2>>> comp(
            N, vector<array<int, 2>>(M, {-1, -1})
        );

        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        auto valid = [&](int r, int c, int mode) {
            if (r < 0 || r >= N || c < 0 || c >= M)
                return false;

            char tile = grid[r][c];

            return tile == '.' ||
                   (tile == 'B' && mode == 0) ||
                   (tile == 'R' && mode == 1);
        };

        int componentID = 0;

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                for (int mode = 0; mode < 2; mode++) {

                    if (!valid(r, c, mode))
                        continue;

                    if (comp[r][c][mode] != -1)
                        continue;

                    queue<tuple<int, int, int>> q;

                    q.push({r, c, mode});
                    comp[r][c][mode] = componentID;

                    while (!q.empty()) {
                        auto [x, y, m] = q.front();
                        q.pop();

                        for (int d = 0; d < 4; d++) {
                            int nx = x + dr[d];
                            int ny = y + dc[d];

                            if (!valid(nx, ny, m))
                                continue;

                            if (comp[nx][ny][m] != -1)
                                continue;

                            comp[nx][ny][m] = componentID;
                            q.push({nx, ny, m});
                        }

                        if (grid[x][y] == '.') {
                            int nm = 1 - m;

                            if (comp[x][y][nm] == -1) {
                                comp[x][y][nm] = componentID;
                                q.push({x, y, nm});
                            }
                        }
                    }

                    componentID++;
                }
            }
        }

        while (Q--) {
            int sr, sc, er, ec;
            cin >> sr >> sc >> er >> ec;

            int start = comp[sr][sc][0];

            bool possible =
                (start == comp[er][ec][0]) ||
                (start == comp[er][ec][1]);

            cout << (possible ? "YES" : "NO") << '\n';
        }
    }
}