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

        vector<int> grid(N * M, 0);

        for (int i = 0; i < Q; ++i) {
            int r_epicenter, c_epicenter, power;
            cin >> r_epicenter >> c_epicenter >> power;

            int r_min = max(0, r_epicenter - power);
            int r_max = min(N - 1, r_epicenter + power);
            int c_min = max(0, c_epicenter - power);
            int c_max = min(M - 1, c_epicenter + power);

            long long p_sq = (long long)power * power;

            for (int r = r_min; r <= r_max; ++r) {
                long long dr = r - r_epicenter;
                long long dr_sq = dr * dr;
                int row_offset = r * M;

                for (int c = c_min; c <= c_max; ++c) {
                    long long dc = c - c_epicenter;
                    long long dist_sq = dr_sq + dc * dc;

                    if (dist_sq <= p_sq) {
                        grid[row_offset + c] = p_sq - dist_sq + 1;
                    }
                }
            }
        }

        for (int r = 0; r < N; ++r) {
            int row_offset = r * M;
            for (int c = 0; c < M; ++c) {
                cout << grid[row_offset + c] << (c == M - 1 ? "" : " ");
            }
            cout << "\n";
        }
    }
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}