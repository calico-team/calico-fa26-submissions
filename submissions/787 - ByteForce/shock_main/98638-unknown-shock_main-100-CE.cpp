#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<long long>> solve(int N, int M, int Q, const vector<vector<long long>>& earthquakes) {
    vector<vector<long long>> grid(N, vector<long long>(M, 0));
    
    for (int i = 0; i < Q; ++i) {
        long long X = earthquakes[i][0];
        long long Y = earthquakes[i][1];
        long long P = earthquakes[i][2];
        
        long long r_epicenter = Y;
        long long c_epicenter = X;
        long long p2 = P * P;
        
        long long row_min = max(0LL, r_epicenter - P);
        long long row_max = min((long long)N - 1, r_epicenter + P);
        long long col_min = max(0LL, c_epicenter - P);
        long long col_max = min((long long)M - 1, c_epicenter + P);
        
        for (long long r = row_min; r <= row_max; ++r) {
            long long dr2 = (r - r_epicenter) * (r - r_epicenter);
            for (long long c = col_min; c <= col_max; ++c) {
                long long ds = dr2 + (c - c_epicenter) * (c - c_epicenter);
                if (ds <= p2) {
                    grid[r][c] = p2 - ds + 1;
                }
            }
        }
    }
    return grid;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<vector<long long>> earthquakes(Q, vector<long long>(3));
        for (int i = 0; i < Q; ++i) {
            cin >> earthquakes[i][0] >> earthquakes[i][1] >> earthquakes[i][2];
        }
        vector<vector<long long>> answer = solve(N, M, Q, earthquakes);
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                cout << answer[r][c] << (c == M - 1 ? "" : " ");
            }
            cout << "\n";
        }
    }
    return 0;
}
```[cite: 2, 3, 5]