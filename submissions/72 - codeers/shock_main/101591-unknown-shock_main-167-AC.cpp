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
    // YOUR CODE HERE
    // NOTE: main() reads each earthquake line as "X Y P", and the input format
    // is "Ri Ci Pi", so X[i] holds the ROW and Y[i] holds the COLUMN,
    // despite what the doc comment above says.

    vector<vector<int>> ans(N, vector<int>(M, 0));

    // nxt[r][c] = smallest unfilled column >= c in row r (M is a sentinel)
    vector<vector<int>> nxt(N, vector<int>(M + 1));
    for (int r = 0; r < N; r++)
        for (int c = 0; c <= M; c++) nxt[r][c] = c;

    // Process earthquakes from last to first: a cell's final value comes from
    // the last earthquake that reaches it, so each cell is filled only once.
    for (int i = Q - 1; i >= 0; i--) {
        long long p = P[i], p2 = p * p;
        for (int dy = -P[i]; dy <= P[i]; dy++) {
            int r = X[i] + dy;
            if (r < 0 || r >= N) continue;
            long long rem = p2 - (long long)dy * dy;
            long long w = (long long)sqrtl((long double)rem);
            while (w * w > rem) w--;
            while ((w + 1) * (w + 1) <= rem) w++;
            int lo = (int)max<long long>(0, Y[i] - w);
            int hi = (int)min<long long>(M - 1, Y[i] + w);
            vector<int>& row = nxt[r];
            auto fnd = [&](int x) {
                int rt = x;
                while (row[rt] != rt) rt = row[rt];
                while (row[x] != rt) { int t = row[x]; row[x] = rt; x = t; }
                return rt;
            };
            int c = fnd(lo);
            while (c <= hi) {
                long long dx = c - Y[i];
                ans[r][c] = (int)(rem - dx * dx + 1);
                row[c] = c + 1;
                c = fnd(c + 1);
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