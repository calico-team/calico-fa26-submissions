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

        // store earthquakes so we can process them backwards
        vector<array<int,3>> eq(Q);
        for (int i = 0; i < Q; ++i) {
            cin >> eq[i][0] >> eq[i][1] >> eq[i][2]; // R, C, P
        }

        // flat grid for speed and cache friendliness
        vector<ll> grid(N * M, 0);

        // process from the last earthquake to the first
        for (int i = Q - 1; i >= 0; --i) {
            int R = eq[i][0];
            int C = eq[i][1];
            int P = eq[i][2];
            ll P2 = 1LL * P * P;

            // disk is guaranteed to lie completely inside the grid
            for (int dr = -P; dr <= P; ++dr) {
                int r = R + dr;
                ll dr2 = 1LL * dr * dr;
                for (int dc = -P; dc <= P; ++dc) {
                    ll d2 = dr2 + 1LL * dc * dc;
                    if (d2 > P2) continue;

                    int c = C + dc;
                    int idx = r * M + c;
                    if (grid[idx] == 0) {               // still untouched
                        grid[idx] = P2 - d2 + 1;
                    }
                }
            }
        }

        // output
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                if (c) cout << ' ';
                cout << grid[r * M + c];
            }
            cout << '\n';
        }
    }
    return 0;
}