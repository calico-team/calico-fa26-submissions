#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const long long INF = 2.5e18;

struct State {
    int r, c, mode;
};

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
        
        // Memoization table for starting positions
        vector<vector<vector<long long>>> memo(N, vector<vector<long long>>(M));
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        auto get_idx = [&](int r, int c, int m) {
            return (r * M + c) * 2 + m;
        };

        for (int i = 0; i < Q; ++i) {
            int sr, sc, er, ec;
            long long k;
            cin >> sr >> sc >> er >> ec >> k;
            
            // If we haven't run BFS from this starting location yet, compute and store it
            if (memo[sr][sc].empty()) {
                int total_states = N * M * 2;
                vector<long long> dist(total_states, INF);
                
                // Safe queue size with ample buffer to prevent any out-of-bounds run errors
                vector<State> q(total_states * 2 + 10);
                int head = 0, tail = 0;
                
                int start_idx = get_idx(sr, sc, 0);
                dist[start_idx] = 0;
                q[tail++] = {sr, sc, 0};
                
                while (head < tail) {
                    State curr = q[head++];
                    int curr_idx = get_idx(curr.r, curr.c, curr.mode);
                    long long curr_d = dist[curr_idx];
                    
                    // Optimization: if popped distance is outdated, skip
                    if (curr_d > dist[curr_idx]) continue;
                    
                    // 1. Move to adjacent cells
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
                                int nidx = get_idx(nr, nc, curr.mode);
                                if (dist[nidx] > curr_d + 1) {
                                    dist[nidx] = curr_d + 1;
                                    q[tail++] = {nr, nc, curr.mode};
                                }
                            }
                        }
                    }
                    
                    // 2. Spin action if standing on a normal tile
                    if (grid[curr.r][curr.c] == '.') {
                        int new_mode = 1 - curr.mode;
                        int nidx = get_idx(curr.r, curr.c, new_mode);
                        if (dist[nidx] > curr_d + 1) {
                            dist[nidx] = curr_d + 1;
                            q[tail++] = {curr.r, curr.c, new_mode};
                        }
                    }
                }
                memo[sr][sc] = move(dist);
            }
            
            const auto& dist = memo[sr][sc];
            long long ans_d = min(dist[get_idx(er, ec, 0)], dist[get_idx(er, ec, 1)]);
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