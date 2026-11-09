#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<int>> solve(int N, int M, int Q, vector<int>& X, vector<int>& Y, vector<int>& P) {
    vector<vector<int>> grid(N, vector<int>(M, 0));
    vector<vector<int>> nxt(N, vector<int>(M + 1));
    for (int r = 0; r < N; r++) {
        for (int c = 0; c <= M; c++) {
            nxt[r][c] = c;
        }
    }

    for (int i = Q - 1; i >= 0; i--) {
        int r0 = X[i];
        int c0 = Y[i];
        int p = P[i];
        for (int dy = -p; dy <= p; dy++) {
            int r = r0 + dy;
            int rest = p * p - dy * dy;
            int w = (int)sqrt((double)rest);
            while (w * w > rest) w--;
            while ((w + 1) * (w + 1) <= rest) w++;
            int right = c0 + w;
            vector<int>& jump = nxt[r];

            int c = c0 - w;
            int start = c;
            while (jump[c] != c) c = jump[c];
            while (jump[start] != c) {
                int up = jump[start];
                jump[start] = c;
                start = up;
            }

            while (c <= right) {
                int dx = c - c0;
                grid[r][c] = rest - dx * dx + 1;
                jump[c] = c + 1;
                int d = c + 1;
                while (jump[d] != d) d = jump[d];
                jump[c] = d;
                c = d;
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