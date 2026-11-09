#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct RowDSU {
    vector<int> parent;
    RowDSU(int m) {
        parent.resize(m + 2);
        for (int i = 0; i <= m + 1; ++i) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
};

vector<vector<int>> solve(int N, int M, int Q, vector<int>& X, vector<int>& Y, vector<int>& P) {
    vector<vector<int>> grid(N, vector<int>(M, 0));
    
    vector<RowDSU> rows_dsu;
    for (int i = 0; i < N; ++i) {
        rows_dsu.emplace_back(M);
    }

    for (int i = Q - 1; i >= 0; --i) {
        int C_i = X[i];
        int R_i = Y[i];
        long long P_i = P[i];
        long long P_i_sq = P_i * P_i;

        int r_min = max(0, (int)(R_i - P_i));
        int r_max = min(N - 1, (int)(R_i + P_i));

        for (int r = r_min; r <= r_max; ++r) {
            long long dx = r - R_i;
            long long max_dc_sq = P_i_sq - dx * dx;
            if (max_dc_sq < 0) continue;
            long long max_dc = sqrt(max_dc_sq);
            
            while ((max_dc + 1) * (max_dc + 1) <= max_dc_sq) max_dc++;
            while (max_dc * max_dc > max_dc_sq) max_dc--;

            int c_min = max(0, (int)(C_i - max_dc));
            int c_max = min(M - 1, (int)(C_i + max_dc));

            int c = rows_dsu[r].find(c_min);
            while (c <= c_max) {
                long long dc = c - C_i;
                grid[r][c] = P_i_sq - (dx * dx + dc * dc) + 1;
                
                rows_dsu[r].parent[c] = rows_dsu[r].find(c + 1);
                c = rows_dsu[r].find(c);
            }
        }
    }

    return grid;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int N, M, Q; cin >> N >> M >> Q;
        vector<int> X(Q), Y(Q), P(Q);
        for (int i = 0; i < Q; i++) {
            cin >> X[i] >> Y[i] >> P[i];
        }
        vector<vector<int>> answer = solve(N, M, Q, X, Y, P);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (j > 0) cout << ' ';
                cout << answer[i][j];
            }
            cout << '\n';
        }
    }
    return 0;
}