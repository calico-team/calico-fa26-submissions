#include <bits/stdc++.h>
using namespace std;

int N, M;

bool canReach(vector<string>& grid, int sr, int sc,
              int er, int ec, int K) {
    
    vector<vector<vector<int>>> dist(
        N, vector<vector<int>>(M, vector<int>(2, -1))
    );

    queue<tuple<int, int, int>> q;

    dist[sr][sc][0] = 0;
    q.push({sr, sc, 0});

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [r, c, mode] = q.front();
        q.pop();

        int time = dist[r][c][mode];

        if (time > K)
            continue;

        if (r == er && c == ec)
            return true;

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr < 0 || nr >= N || nc < 0 || nc >= M)
                continue;

            char tile = grid[nr][nc];

            bool canMove = false;

            if (tile == '.') {
                canMove = true;
            }
            else if (tile == 'B' && mode == 0) {
                canMove = true;
            }
            else if (tile == 'R' && mode == 1) {
                canMove = true;
            }

            if (canMove && dist[nr][nc][mode] == -1) {
                dist[nr][nc][mode] = time + 1;
                q.push({nr, nc, mode});
            }
        }

        if (grid[r][c] == '.') {
            int newMode = 1 - mode;

            if (dist[r][c][newMode] == -1) {
                dist[r][c][newMode] = time + 1;
                q.push({r, c, newMode});
            }
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    // Goes through ALL test cases
    while (T--) {
        int Q;
        cin >> N >> M >> Q;

        vector<string> grid(N);
        for (int i = 0; i < N; i++) {
            cin >> grid[i];
        }

        while (Q--) {
            int sr, sc, er, ec, K;
            cin >> sr >> sc >> er >> ec >> K;

            if (canReach(grid, sr, sc, er, ec, K))
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }

    return 0;
}