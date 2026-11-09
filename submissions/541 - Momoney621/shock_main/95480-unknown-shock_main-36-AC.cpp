#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<int>> solve(int N, int M, int Q, vector<int>& X, vector<int>& Y, vector<int>& P) {
    vector<vector<int>> answer(N, vector<int>(M, 0));
    vector<int> next(N * (M + 1));
    for (int r = 0; r < N; r++)
        for (int c = 0; c <= M; c++) next[r * (M + 1) + c] = c;

    for (int q = Q - 1; q >= 0; q--) {
        for (int dr = -P[q]; dr <= P[q]; dr++) {
            int row = X[q] + dr;
            int span = P[q] * P[q] - dr * dr;
            int reach = sqrt(span);
            int* link = &next[row * (M + 1)];
            auto unassigned = [&](int c) {
                while (link[c] != c) {
                    link[c] = link[link[c]];
                    c = link[c];
                }
                return c;
            };
            for (int c = unassigned(Y[q] - reach); c <= Y[q] + reach; c = unassigned(c + 1)) {
                answer[row][c] = span - (c - Y[q]) * (c - Y[q]) + 1;
                link[c] = c + 1;
            }
        }
    }
    return answer;
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
