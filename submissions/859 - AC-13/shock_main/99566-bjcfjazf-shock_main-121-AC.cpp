#include <iostream>
#include <vector>
#include<cmath>
using namespace std;

/**
 * Return the reading of every seismometer after all Q earthquakes have
 * occurred: an N by M grid of integers, where each reading is the shock
 * level of the most recent earthquake that reached that block (0 if no
 * earthquake reached it).
 *
 * N: the number of rows of blocks
 * M: the number of columns of blocks
 * Q: the number of earthquakes
 * X: the column of the epicenter of the i-th earthquake, in occurrence order
 * Y: the row of the epicenter of the i-th earthquake, in occurrence order
 * P: the power of the i-th earthquake, in occurrence order
 */
vector<vector<int>> solve(int N, int M, int Q, vector<int>& X, vector<int>& Y, vector<int>& P) {
    vector<vector<int>> answer(N, vector<int>(M, 0));
    vector<vector<int>> next_c(N, vector<int>(M + 1));
    for (int row = 0; row < N; row++) {
        for (int col = 0; col <= M; col++) {
            next_c[row][col] = col;
        }
    }

    auto get_next = [&](auto& self, int row, int col) -> int {
        if (next_c[row][col] == col) return col;
        return next_c[row][col] = self(self, row, next_c[row][col]);
    };

    for (int i = Q - 1; i >= 0; i--) {
        int Ri = X[i];
        int Ci = Y[i];
        long long Pi = P[i];
        long long Pi_sq = Pi * Pi;

        int r_min = max(0, (int)(Ri - Pi));
        int r_max = min(N - 1, (int)(Ri + Pi));

        for (int row = r_min; row <= r_max; row++) {
            long long dr = row - Ri;
            long long rem_sq = Pi_sq - dr * dr;
            if (rem_sq < 0) continue;

            long long dc = (long long)sqrt((double)rem_sq);
            int c_min = max(0, (int)(Ci - dc));
            int c_max = min(M - 1, (int)(Ci + dc));

            int c = get_next(get_next, row, c_min);
            while (c <= c_max) {
                long long dc_val = c - Ci;
                long long dist_sq = dr * dr + dc_val * dc_val;
                
                answer[row][c] = (int)(Pi_sq - dist_sq + 1);
                next_c[row][c] = get_next(get_next, row, c + 1);
                c = next_c[row][c];
            }
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; 
    cin >> T;
    while (T--) {
        int N, M, Q; 
        cin >> N >> M >> Q;
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