#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<int>> solve(int N, int M, int Q, vector<int>& X, vector<int>& Y, vector<int>& P) {
    vector<vector<int>> ans(N, vector<int>(M, 0));
    vector<int> parent(N * (M + 1));
    for (int i = 0; i < N * (M + 1); i++) parent[i] = i;

    auto find = [&](auto& self, int i) -> int {
        return parent[i] == i ? i : parent[i] = self(self, parent[i]);
    };

    for (int q = Q - 1; q >= 0; q--) {
        int center_c = X[q];
        int center_r = Y[q];
        long long p = P[q];
        int r_min = max(0, (int)(center_r - p));
        int r_max = min(N - 1, (int)(center_r + p));

        for (int r = r_min; r <= r_max; r++) {
            long long dy = abs(r - center_r);
            long long rem = p * p - dy * dy;
            if (rem < 0) continue;
            int dx = sqrt(rem);
            int c_left = max(0, center_c - dx);
            int c_right = min(M - 1, center_c + dx);

            int base = r * (M + 1);
            int curr = find(find, base + c_left);
            while (curr <= base + c_right) {
                int c = curr - base;
                long long dist2 = dy * dy + (long long)(c - center_c) * (c - center_c);
                ans[r][c] = (int)(p * p - dist2 + 1);
                parent[curr] = find(find, curr + 1);
                curr = find(find, curr);
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; if (!(cin >> T)) return 0;
    while (T--) {
        int N, M, Q; cin >> N >> M >> Q;
        vector<int> X(Q), Y(Q), P(Q);
        for (int i = 0; i < Q; i++) cin >> Y[i] >> X[i] >> P[i]; // Input has row then col
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