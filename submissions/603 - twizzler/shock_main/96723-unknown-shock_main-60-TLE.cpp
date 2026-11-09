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

        for (int i = Q - 1; i >= 0; i--) {
            int R = quakes[i][0];
            int C = quakes[i][1];
            int P = quakes[i][2];
            long long P2 = 1LL * P * P;

            for (int dr = -P; dr <= P; dr++) {
                for (int dc = -P; dc <= P; dc++) {
                    if (1LL * dr * dr + 1LL * dc * dc <= P2) {
                        int r = R + dr;
                        int c = C + dc;
                        if (grid[r][c] == 0) {
                            grid[r][c] = int(P2 - (1LL * dr * dr + 1LL * dc * dc) + 1);
                        }
                    }
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
