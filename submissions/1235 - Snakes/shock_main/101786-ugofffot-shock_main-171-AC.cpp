#include <iostream>
#include <vector>
#include <numeric>
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
    vector<vector<int>> a(N, vector<int>(M, 0));
    vector<int> nx(N * (M + 1));
    iota(nx.begin(), nx.end(), 0);
    auto find = [&](int x) { while (nx[x] != x) x = nx[x] = nx[nx[x]]; return x; };
    for (int i = Q - 1; i >= 0; i--) {
        int r0 = X[i], c0 = Y[i], p = P[i];
        for (int r = r0 - p; r <= r0 + p; r++) {
            int v = p * p - (r - r0) * (r - r0), w = sqrt(v), b = r * (M + 1);
            for (int c = find(b + c0 - w); c - b <= c0 + w; c = find(c))
                a[r][c - b] = v - (c - b - c0) * (c - b - c0) + 1, nx[c] = c + 1;
        }
    }
    return a;
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
