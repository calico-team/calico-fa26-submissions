#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

const long long INF = 2e18;

struct State {
    int r, c, mode;
};

static State q_arr[80005];

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
        
        int total_states = N * M * 2;
        unordered_map<int, vector<long long>> memo;
        memo.reserve(512);
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        auto get_idx = [&](int r, int c, int m) {
            return (r * M + c) * 2 + m;
        };

        for (int i = 0; i < Q; ++i) {
            int sr, sc, er, ec;
            long long k;
            cin >> sr >> sc >> er >> ec >> k;
            
            int start_key = sr * M + sc;
            
            auto it = memo.find(start_key);
            if (it == memo.end()) {
                if (memo.size() >= 400) {
                    memo.clear();
                }
                
                vector<long long> dist(total_states, INF);
                int head = 0, tail = 0;
                
                int start_idx = get_idx(sr, sc, 0);
                dist[start_idx] = 0;
                q_arr[tail++] = {sr, sc, 0};
                
                while (head < tail) {
                    State curr = q_arr[head++];
                    int curr_idx = get_idx(curr.r, curr.c, curr.mode);
                    
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
                                if (dist[nidx] > dist[curr_idx] + 1) {
                                    dist[nidx] = dist[curr_idx] + 1;
                                    q_arr[tail++] = {nr, nc, curr.mode};
                                }
                            }
                        }
                    }
                    
                    if (grid[curr.r][curr.c] == '.') {
                        int new_mode = 1 - curr.mode;
                        int nidx = get_idx(curr.r, curr.c, new_mode);
                        if (dist[nidx] > dist[curr_idx] + 1) {
                            dist[nidx] = dist[curr_idx] + 1;
                            q_arr[tail++] = {curr.r, curr.c, new_mode};
                        }
                    }
                }
                it = memo.emplace(start_key, move(dist)).first;
            }
            
            const auto& dist = it->second;
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