#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<array<int, 3>> eq(Q);
        for (int i = 0; i < Q; ++i) {
            cin >> eq[i][0] >> eq[i][1] >> eq[i][2]; // R, C, P
        }

        // Flat grid: 0 means never written
        vector<ll> grid(static_cast<size_t>(N) * M, 0);

        // Process from last earthquake to first
        for (int i = Q - 1; i >= 0; --i) {
            int R = eq[i][0];
            int C = eq[i][1];
            int P = eq[i][2];
            ll P2 = 1LL * P * P;

            // Disk is guaranteed to lie completely inside the grid
            for (int dr = -P; dr <= P; ++dr) {
                int r = R + dr;
                ll dr2 = 1LL * dr * dr;

                for (int dc = -P; dc <= P; ++dc) {
                    ll d2 = dr2 + 1LL * dc * dc;
                    if (d2 > P2) continue;

                    int c = C + dc;
                    size_t idx = static_cast<size_t>(r) * M + c;

                    if (grid[idx] == 0) {
                        grid[idx] = P2 - d2 + 1;
                    }
                }
            }
        }

        // Output
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                if (c) cout << ' ';
                cout << grid[static_cast<size_t>(r) * M + c];
            }
            cout << '\n';
        }
    }

    return 0;
}