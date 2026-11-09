#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

bool is_active(int r, int c, int mode, const vector<string>& grid) {
    char tile = grid[r][c];
    if (tile == '.') return true;
    if (tile == 'B' && mode == 0) return true;
    if (tile == 'R' && mode == 1) return true;
    return false;
}

void solve() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> grid(N);
        for (int i = 0; i < N; ++i) {
            cin >> grid[i];
        }

        struct Query {
            int r_start, c_start, r_end, c_end;
        };
        vector<Query> queries(Q);
        for (int i = 0; i < Q; ++i) {
            cin >> queries[i].r_start >> queries[i].c_start >> queries[i].r_end >> queries[i].c_end;
        }

        vector<vector<vector<bool>>> visited(N, vector<vector<bool>>(M, vector<bool>(2, false)));
        queue<tuple<int, int, int>> q;

        int dest_r = N - 1;
        int dest_c = M - 1;
        char dest_tile = grid[dest_r][dest_c];

        if (dest_tile == '.') {
            visited[dest_r][dest_c][0] = true;
            visited[dest_r][dest_c][1] = true;
            q.push(make_tuple(dest_r, dest_c, 0));
            q.push(make_tuple(dest_r, dest_c, 1));
        } else if (dest_tile == 'B') {
            visited[dest_r][dest_c][0] = true;
            q.push(make_tuple(dest_r, dest_c, 0));
        } else if (dest_tile == 'R') {
            visited[dest_r][dest_c][1] = true;
            q.push(make_tuple(dest_r, dest_c, 1));
        }

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            int r = get<0>(q.front());
            int c = get<1>(q.front());
            int mode = get<2>(q.front());
            q.pop();

            if (grid[r][c] == '.') {
                int other_mode = 1 - mode;
                if (!visited[r][c][other_mode]) {
                    visited[r][c][other_mode] = true;
                    q.push(make_tuple(r, c, other_mode));
                }
            }

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                    if (!visited[nr][nc][mode] && is_active(nr, nc, mode, grid)) {
                        visited[nr][nc][mode] = true;
                        q.push(make_tuple(nr, nc, mode));
                    }
                }
            }
        }

        for (int i = 0; i < Q; ++i) {
            int r_start = queries[i].r_start;
            int c_start = queries[i].c_start;
            if (visited[r_start][c_start][0]) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}

int main() {
    solve();
    return 0;
}