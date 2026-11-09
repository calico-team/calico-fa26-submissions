#include <iostream>
#include <vector>
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
    vector<vector<int>> ans(N, vector<int>(M, 0));
    vector<int> parent(N * (M + 1));
    for (int r = 0; r < N; r++) {
        int base = r * (M + 1);
        for (int c = 0; c <= M; c++) {
            parent[base + c] = base + c;
        }
    }
    auto find = [&](int x) {
        int root = x;
        while (parent[root] != root) {
            root = parent[root];
        }
        while (parent[x] != x) {
            int nxt = parent[x];
            parent[x] = root;
            x = nxt;
        }
        return root;
    };
    for (int i = Q - 1; i >= 0; i--) {
        int cy = X[i];
        int cx = Y[i];
        int p = P[i];
        long long p2 = 1LL * p * p;
        int dx = p;
        for (int d = 0; d <= p; d++) {
            while (1LL * dx * dx + 1LL * d * d > p2) {
                dx--;
            }
            for (int sign = -1; sign <= 1; sign += 2) {
                if (d == 0 && sign == 1) continue;
                int r = cy + sign * d;
                if (r < 0 || r >= N) continue;
                int left = cx - dx;
                int right = cx + dx;
                int base = r * (M + 1);
                int c = find(base + left);
                while (c <= base + right) {
                    int col = c - base;
                    long long dist2 =
                        1LL * d * d +
                        1LL * (col - cx) * (col - cx);
                    ans[r][col] = (int)(p2 - dist2 + 1);
                    parent[c] = find(c + 1);
                    c = parent[c];
                }
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
