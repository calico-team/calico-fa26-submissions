#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
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
    // NOTE: main() reads each earthquake line "R C P" into X, Y, P,
    // so X[i] is actually the ROW and Y[i] the COLUMN of the epicenter.
    int W = M + 1; // one sentinel column per row
    vector<int> nxt(N * W);
    for (int r = 0; r < N; r++)
        for (int c = 0; c <= M; c++) nxt[r * W + c] = r * W + c;
    auto find = [&](int x) {
        int root = x;
        while (nxt[root] != root) root = nxt[root];
        while (nxt[x] != root) { int t = nxt[x]; nxt[x] = root; x = t; }
        return root;
    };
    vector<vector<int>> ans(N, vector<int>(M, 0));
    for (int i = Q - 1; i >= 0; i--) {
        int R = X[i], C = Y[i];
        long long p = P[i];
        for (int dr = -P[i]; dr <= P[i]; dr++) {
            int r = R + dr;
            if (r < 0 || r >= N) continue;
            long long rem = p * p - (long long)dr * dr;
            long long w = (long long)sqrtl((long double)rem);
            while (w * w > rem) w--;
            while ((w + 1) * (w + 1) <= rem) w++;
            int lo = max<long long>(0, C - w), hi = min<long long>(M - 1, C + w);
            int j = find(r * W + lo) - r * W;
            while (j <= hi) {
                long long dc = j - C;
                ans[r][j] = (int)(rem - dc * dc + 1);
                nxt[r * W + j] = r * W + j + 1;
                j = find(r * W + j + 1) - r * W;
            }
        }
    }
    return ans;
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
