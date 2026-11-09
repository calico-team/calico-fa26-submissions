#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

bool is_active(int r, int c, int mode, const vector<string>& grid) {
    char tile = grid[r][c];
    if (tile == '.') return true;
    if (tile == 'B' && mode == 0) return true; // Blue mode
    if (tile == 'R' && mode == 1) return true; // Red mode
    return false;
}

void solve() {
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

        vector<vector<vector<int>>> visited(N, vector<vector<int>>(M, vector<int>(2, 0)));

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int q_id = 1; q_id <= Q; ++q_id) {
            int r_start, c_start, r_end, c_end;
            cin >> r_start >> c_start >> r_end >> c_end;

            if (r_start == r_end && c_start == c_end) {
                cout << "YES\n";
                continue;
            }

            queue<tuple<int, int, int>> q;
            
            visited[r_start][c_start][0] = q_id;
            q.push(make_tuple(r_start, c_start, 0));

            bool possible = false;

            while (!q.empty()) {
                int r = get<0>(q.front());
                int c = get<1>(q.front());
                int mode = get<2>(q.front());
                q.pop();

                if (r == r_end && c == c_end) {
                    possible = true;
                    break;
                }

                if (grid[r][c] == '.') {
                    int other_mode = 1 - mode;
                    if (visited[r][c][other_mode] != q_id) {
                        visited[r][c][other_mode] = q_id;
                        q.push(make_tuple(r, c, other_mode));
                    }
                }

                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                        if (visited[nr][nc][mode] != q_id && is_active(nr, nc, mode, grid)) {
                            visited[nr][nc][mode] = q_id;
                            q.push(make_tuple(nr, nc, mode));
                        }
                    }
                }
            }

            if (possible) {
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