#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int N, M, Q;
    if (!(cin >> N >> M >> Q)) return;
    vector<vector<int>> grid(N, vector<int>(M, 0));
    for (int i = 0; i < Q; ++i) {
        int r_e, c_e, p_e;
        cin >> r_e >> c_e >> p_e;
        long long p_sq = (long long)p_e * p_e;
        int r_min = max(0, r_e - p_e);
        int r_max = min(N - 1, r_e + p_e);
        int c_min = max(0, c_e - p_e);
        int c_max = min(M - 1, c_e + p_e);
        for (int r = r_min; r <= r_max; ++r) {
            long long rd2 = (long long)(r - r_e) * (r - r_e);
            for (int c = c_min; c <= c_max; ++c) {
                long long d2 = rd2 + (long long)(c - c_e) * (c - c_e);
                if (d2 <= p_sq) {
                    grid[r][c] = (int)(p_sq - d2 + 1);
                }
            }
        }
    }
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            cout << grid[r][c] << (c == M - 1 ? "" : " ");
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}