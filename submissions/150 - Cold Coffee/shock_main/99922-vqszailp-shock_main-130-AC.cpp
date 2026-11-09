#include <iostream>
#include <vector>
#include <cmath>
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
    vector<vector<int>> g(N, vector<int>(M, 0));
    int W = M + 1;
    vector<int> f(N * W);
    for (int i = 0; i < (int)f.size(); i++) f[i] = i;

    for (int t = Q - 1; t >= 0; t--) {
        int r = X[t], c = Y[t], p = P[t];
        int pp = p * p;
        for (int i = r - p; i <= r + p; i++) {
            int dd = (i - r) * (i - r);
            int left = pp - dd;
            int rad = (int)sqrt((double)left);
            while (1LL * (rad + 1) * (rad + 1) <= left) rad++;
            while (1LL * rad * rad > left) rad--;
            int base = i * W;
            int j = base + c - rad;
            while (f[j] != j) {
                f[j] = f[f[j]];
                j = f[j];
            }
            int end = base + c + rad;
            while (j <= end) {
                int y = j - base;
                g[i][y] = pp - dd - (y - c) * (y - c) + 1;
                int nj = j + 1;
                while (f[nj] != nj) {
                    f[nj] = f[f[nj]];
                    nj = f[nj];
                }
                f[j] = nj;
                j = nj;
            }
        }
    }
    return g;
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
