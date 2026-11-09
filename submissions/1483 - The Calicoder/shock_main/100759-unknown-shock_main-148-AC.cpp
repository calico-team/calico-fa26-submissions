#include <bits/stdc++.h>
using namespace std;

struct Earthquake {
    int r, c, p;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<Earthquake> earthquakes(Q);

        for (int i = 0; i < Q; i++) {
            cin >> earthquakes[i].r
                >> earthquakes[i].c
                >> earthquakes[i].p;
        }

        vector<vector<int>> ans(N, vector<int>(M, 0));

        vector<vector<int>> parent(N, vector<int>(M + 1));

        for (int r = 0; r < N; r++) {
            iota(parent[r].begin(), parent[r].end(), 0);
        }

        auto find = [&](int r, int c) {
            int x = c;

            while (parent[r][x] != x) {
                x = parent[r][x];
            }

            while (parent[r][c] != c) {
                int next = parent[r][c];
                parent[r][c] = x;
                c = next;
            }

            return x;
        };

        for (int i = Q - 1; i >= 0; i--) {
            int R = earthquakes[i].r;
            int C = earthquakes[i].c;
            int P = earthquakes[i].p;

            for (int r = R - P; r <= R + P; r++) {
                int dr = r - R;

                int remaining = P * P - dr * dr;

                int width = sqrt(remaining);

                while ((width + 1) * (width + 1) <= remaining)
                    width++;

                while (width * width > remaining)
                    width--;

                int left = C - width;
                int right = C + width;

                int c = find(r, left);

                while (c <= right) {
                    int dc = c - C;

                    ans[r][c] = remaining - dc * dc + 1;

                    parent[r][c] = find(r, c + 1);

                    c = find(r, c);
                }
            }
        }

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                if (c > 0) cout << ' ';
                cout << ans[r][c];
            }
            cout << '\n';
        }
    }
}