#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<vector<int>> grid(N, vector<int>(M, 0));
        vector<array<int, 3>> quakes(Q);

        for (int i = 0; i < Q; i++) {
            cin >> quakes[i][0] >> quakes[i][1] >> quakes[i][2];
        }

        vector<set<int>> free_cols(N);
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                free_cols[r].insert(c);
            }
        }

        for (int i = Q - 1; i >= 0; i--) {
            int R = quakes[i][0];
            int C = quakes[i][1];
            int P = quakes[i][2];
            long long P2 = 1LL * P * P;

            for (int dr = -P; dr <= P; dr++) {
                long long rem = P2 - 1LL * dr * dr;
                if (rem < 0) continue;

                int dcmax = (int)sqrt((long double)rem);
                while (1LL * (dcmax + 1) * (dcmax + 1) <= rem) ++dcmax;
                while (1LL * dcmax * dcmax > rem) --dcmax;

                int r = R + dr;
                int L = C - dcmax;
                int Rg = C + dcmax;

                auto& s = free_cols[r];
                auto it = s.lower_bound(L);
                while (it != s.end() && *it <= Rg) {
                    int c = *it;
                    long long dc = c - C;
                    grid[r][c] = int(P2 - (1LL * dr * dr + dc * dc) + 1);
                    it = s.erase(it);
                }
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (j) cout << ' ';
                cout << grid[i][j];
            }
            cout << '\n';
        }
    }
    return 0;
}
