#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

const long long INF = 2e18;

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
        
        unordered_map<int, vector<long long>> memo;
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        auto get_idx = [&](int r, int c, int m, int M_val) {
            return (r * M_val + c) * 2 + m;
        };

        for (int i = 0; i < Q; ++i) {
            int sr, sc, er, ec;
            long long k;
            cin >> sr >> sc >> er >> ec >> k;
            
            int start_key = sr * M + sc;
            
            if (memo.find(start_key) == memo.end()) {
                if (memo.size() >= 128) {
                    memo.clear();
                }
                
                vector<long long> dist(N * M * 2, INF);
                queue<State> q;
                
                int start_idx = get_idx(sr, sc, 0, M);
                dist[start_idx] = 0;
                q.push({sr, sc, 0});
                
                while (!q.empty()) {
                    State curr = q.front();
                    q.pop();
                    
                    int curr_idx = get_idx(curr.r, curr.c, curr.mode, M);
                    
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
                                int nidx = get_idx(nr, nc, curr.mode, M);
                                if (dist[nidx] > dist[curr_idx] + 1) {
                                    dist[nidx] = dist[curr_idx] + 1;
                                    q.push({nr, nc, curr.mode});
                                }
                            }
                        }
                    }
                    
                    if (grid[curr.r][curr.c] == '.') {
                        int new_mode = 1 - curr.mode;
                        int nidx = get_idx(curr.r, curr.c, new_mode, M);
                        if (dist[nidx] > dist[curr_idx] + 1) {
                            dist[nidx] = dist[curr_idx] + 1;
                            q.push({curr.r, curr.c, new_mode});
                        }
                    }
                }
                memo[start_key] = move(dist);
            }
            
            const auto& dist = memo[start_key];
            long long ans_d = min(dist[get_idx(er, ec, 0, M)], dist[get_idx(er, ec, 1, M)]);
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