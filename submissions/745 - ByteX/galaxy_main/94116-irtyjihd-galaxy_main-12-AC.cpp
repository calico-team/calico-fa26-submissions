#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n, m, q;
        scanf("%d %d %d", &n, &m, &q);

        char grid[205][205];
        int component[205][205] = {};

        for (int i = 0; i < n; i++) {
            scanf("%s", grid[i]);
        }

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};
        int cnt = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (component[i][j] != 0) continue;

                cnt++;
                queue<pair<int, int>> bfs;
                bfs.push({i, j});
                component[i][j] = cnt;

                while (!bfs.empty()) {
                    int r = bfs.front().first;
                    int c = bfs.front().second;
                    bfs.pop();

                    for (int k = 0; k < 4; k++) {
                        int nr = r + dr[k];
                        int nc = c + dc[k];

                        if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                        if (component[nr][nc] != 0) continue;

                        // We cannot move directly between red and blue tiles.
                        if (grid[r][c] == 'R' && grid[nr][nc] == 'B') continue;
                        if (grid[r][c] == 'B' && grid[nr][nc] == 'R') continue;

                        component[nr][nc] = cnt;
                        bfs.push({nr, nc});
                    }
                }
            }
        }

        while (q--) {
            int r1, c1, r2, c2;
            scanf("%d %d %d %d", &r1, &c1, &r2, &c2);

            if (component[r1][c1] == component[r2][c2]) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }

    return 0;
}
