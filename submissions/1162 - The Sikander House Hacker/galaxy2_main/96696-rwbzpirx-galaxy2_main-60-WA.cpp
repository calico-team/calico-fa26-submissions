#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct State {
    int d, r, c, mode;
    bool operator>(const State& other) const {
        return d > other.d;
    }
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
        
        vector<vector<vector<int>>> memo(N, vector<vector<int>>(M));
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        auto get_idx = [&](int r, int c, int m, int M_val) {
            return (r * M_val + c) * 2 + m;
        };

        for (int i = 0; i < Q; ++i) {
            int sr, sc, er, ec, k;
            cin >> sr >> sc >> er >> ec >> k;
            
            if (memo[sr][sc].empty()) {
                vector<int> dist(N * M * 2, INF);
                dist[get_idx(sr, sc, 0, M)] = 0;
                priority_queue<State, vector<State>, greater<State>> pq;
                pq.push({0, sr, sc, 0});
                
                while (!pq.empty()) {
                    State curr = pq.top();
                    pq.pop();
                    
                    int idx = get_idx(curr.r, curr.c, curr.mode, M);
                    if (curr.d > dist[idx]) continue;
                    
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
                                int nd = curr.d + 1;
                                int nidx = get_idx(nr, nc, curr.mode, M);
                                if (nd < dist[nidx]) {
                                    dist[nidx] = nd;
                                    pq.push({nd, nr, nc, curr.mode});
                                }
                            }
                        }
                    }
                    
                    if (grid[curr.r][curr.c] == '.') {
                        int new_mode = 1 - curr.mode;
                        int nd = curr.d + 1;
                        int nidx = get_idx(curr.r, curr.c, new_mode, M);
                        if (nd < dist[nidx]) {
                            dist[nidx] = nd;
                            pq.push({nd, curr.r, curr.c, new_mode});
                        }
                    }
                }
                memo[sr][sc] = dist;
            }
            
            const auto& dist = memo[sr][sc];
            int ans_d = min(dist[get_idx(er, ec, 0, M)], dist[get_idx(er, ec, 1, M)]);
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