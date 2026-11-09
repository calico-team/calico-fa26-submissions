#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct State {
    int r, c, mode; // mode: 0 = Blue, 1 = Red
};

const int dRow[] = {-1, 1, 0, 0};
const int dCol[] = {0, 0, -1, 1};

bool can_walk(char tile, int mode) {
    if (tile == '.') return true;
    if (mode == 0 && tile == 'B') return true;
    if (mode == 1 && tile == 'R') return true;
    return false;
}

void solve() {
    int H, W, Q;
    if (!(cin >> H >> W >> Q)) return;

    vector<string> board(H);
    for (int i = 0; i < H; ++i) {
        cin >> board[i];
    }

    // region[r][c][mode] stores component ID (-1 if unvisited)
    vector<vector<vector<int>>> region(H, vector<vector<int>>(W, vector<int>(2, -1)));
    int current_id = 0;

    // Explore reachable components
    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            for (int m = 0; m < 2; ++m) {
                if (region[r][c][m] != -1 || !can_walk(board[r][c], m)) continue;

                queue<State> q;
                q.push({r, c, m});
                region[r][c][m] = current_id;

                while (!q.empty()) {
                    auto [cr, cc, cm] = q.front();
                    q.pop();

                    // Spin action: toggle mode if standing on '.'
                    if (board[cr][cc] == '.') {
                        int nm = 1 - cm;
                        if (region[cr][cc][nm] == -1) {
                            region[cr][cc][nm] = current_id;
                            q.push({cr, cc, nm});
                        }
                    }

                    // Move to 4 neighboring cells
                    for (int i = 0; i < 4; ++i) {
                        int nr = cr + dRow[i];
                        int nc = cc + dCol[i];

                        if (nr >= 0 && nr < H && nc >= 0 && nc < W) {
                            if (can_walk(board[nr][nc], cm) && region[nr][nc][cm] == -1) {
                                region[nr][nc][cm] = current_id;
                                q.push({nr, nc, cm});
                            }
                        }
                    }
                }
                current_id++;
            }
        }
    }

    // Answer queries
    while (Q--) {
        int sr, sc, tr, tc;
        cin >> sr >> sc >> tr >> tc;

        int start_id = region[sr][sc][0]; // Starts in Blue mode
        int target_mode = (board[tr][tc] == 'R') ? 1 : 0;
        int target_id = region[tr][tc][target_mode];

        if (start_id != -1 && start_id == target_id) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
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
    return 0;
}