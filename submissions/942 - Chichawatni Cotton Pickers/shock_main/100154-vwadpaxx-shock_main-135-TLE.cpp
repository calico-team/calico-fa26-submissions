#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int num_test_cases;
    if (!(cin >> num_test_cases)) return;

    while (num_test_cases--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<vector<int>> grid(N, vector<int>(M, 0));

        for (int i = 0; i < Q; ++i) {
            int r_epicenter, c_epicenter, power;
            cin >> r_epicenter >> c_epicenter >> power;

            int r_min = max(0, r_epicenter - power);
            int r_max = min(N - 1, r_epicenter + power);
            int c_min = max(0, c_epicenter - power);
            int c_max = min(M - 1, c_epicenter + power);

            long long p_sq = (long long)power * power;

            for (int r = r_min; r <= r_max; ++r) {
                long long dr_sq = (long long)(r - r_epicenter) * (r - r_epicenter);
                for (int c = c_min; c <= c_max; ++c) {
                    long long dist_sq = dr_sq + (long long)(c - c_epicenter) * (c - c_epicenter);
                    if (dist_sq <= p_sq) {
                        grid[r][c] = p_sq - dist_sq + 1;
                    }
                }
            }
        }

        // Print the grid
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                cout << grid[r][c] << (c == M - 1 ? "" : " ");
            }
            cout << "\n";
        }
    }
}

int main() {
    // Optimize standard I/O operations for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}