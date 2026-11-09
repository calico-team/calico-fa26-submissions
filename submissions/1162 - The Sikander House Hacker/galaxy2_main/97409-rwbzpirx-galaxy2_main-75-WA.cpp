#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const long long INF = 2.5e18;

struct State {
    int r, c, mode;
};

static State q_arr[80005];
static long long dist_memo[15][4005][2];
static bool visited_start[15][4005];

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
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                visited_start[i][j] = false;
            }
        }
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < Q; ++i) {
            int sr, sc, er, ec;
            long long k;
            cin >> sr >> sc >> er >> ec >> k;
            
            if (!visited_start[sr][sc]) {
                visited_start[sr][sc] = true;
                
                for (int r = 0; r < N; ++r) {
                    for (int c = 0; c < M; ++c) {
                        dist_memo[r][c][0] = INF;
                        dist_memo[r][c][1] = INF;
                    }
                }
                
                int head = 0, tail = 0;
                dist_memo[sr][sc][0] = 0;
                q_arr[tail++] = {sr, sc, 0};
                
                while (head < tail) {
                    State curr = q_arr[head++];
                    long long curr_d = dist_memo[curr.r][curr.c][curr.mode];
                    
                    for (int j = 0; j < 4; ++j) {
                        int nr = curr.r + dr[j];
                        int nc = curr.c + dc[j];
                        if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                            char cell = grid[nr][nc];
                            bool active = false;
                            if (cell == '.') active = true;
                            else if (cell == 'B' && curr.mode == 0) active = true;
                            else if (cell == 'R' && curr.mode == 1) active = true;
                            
                            if (active) {
                                if (dist_memo[nr][nc][curr.mode] > curr_d + 1) {
                                    dist_memo[nr][nc][curr.mode] = curr_d + 1;
                                    q_arr[tail++] = {nr, nc, curr.mode};
                                }
                            }
                        }
                    }
                    
                    if (grid[curr.r][curr.c] == '.') {
                        int new_mode = 1 - curr.mode;
                        if (dist_memo[curr.r][curr.c][new_mode] > curr_d + 1) {
                            dist_memo[curr.r][curr.c][new_mode] = curr_d + 1;
                            q_arr[tail++] = {curr.r, curr.c, new_mode};
                        }
                    }
                }
            }
            
            long long ans_d = min(dist_memo[er][ec][0], dist_memo[er][ec][1]);
            if (ans_d <= k) {
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