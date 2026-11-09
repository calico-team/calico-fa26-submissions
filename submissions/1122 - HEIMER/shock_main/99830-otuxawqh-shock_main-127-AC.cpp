#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<int>> solve(int N, int M, int Q, vector<int>& X, vector<int>& Y, vector<int>& P) {
    vector<vector<int>> ans(N, vector<int>(M, 0)), nxt(N, vector<int>(M + 1));
    for (auto& row : nxt)
        for (int c = 0; c <= M; c++) row[c] = c;

    auto find = [&](int r, int c) {
        int root = c;
        while (nxt[r][root] != root) root = nxt[r][root];
        while (nxt[r][c] != root) {
            int t = nxt[r][c];
            nxt[r][c] = root;
            c = t;
        }
        return root;
    };

    for (int i = Q - 1; i >= 0; i--) {
        int R = X[i], C = Y[i], p = P[i];
        for (int r = R - p; r <= R + p; r++) {
            int rem = p * p - (r - R) * (r - R);
            int w = (int)sqrt((double)rem);
            for (int c = find(r, C - w); c <= C + w; c = find(r, c + 1)) {
                ans[r][c] = rem - (c - C) * (c - C) + 1;
                nxt[r][c] = c + 1;
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
        for (int i = 0; i < Q; i++) cin >> X[i] >> Y[i] >> P[i];
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
