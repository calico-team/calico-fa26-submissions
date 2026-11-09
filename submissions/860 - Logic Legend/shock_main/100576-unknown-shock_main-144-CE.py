# Source: https://usaco.guide/general/io
#include <bits/stdc++.h>
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
        for (auto &e : earthquakes) {
            cin >> e.r >> e.c >> e.p;
        }

        vector<vector<int>> reading(N, vector<int>(M, 0));
        vector<vector<int>> nextUnfilled(N, vector<int>(M + 1));

        for (int r = 0; r < N; ++r) {
            iota(nextUnfilled[r].begin(), nextUnfilled[r].end(), 0);
        }

        auto findNext = [&](auto&& self, int r, int x) -> int {
            if (nextUnfilled[r][x] == x) return x;
            return nextUnfilled[r][x] = self(self, r, nextUnfilled[r][x]);
        };

        for (int i = Q - 1; i >= 0; --i) {
            auto [R, C, P] = earthquakes[i];
            long long p2 = 1LL * P * P;

            for (int r = R - P; r <= R + P; ++r) {
                long long dr = r - R;
                int d = (int)sqrt((long double)(p2 - dr * dr));

                int left = C - d;
                int right = C + d;

                int c = findNext(findNext, r, left);
                while (c <= right) {
                    long long dc = c - C;
                    reading[r][c] = (int)(p2 - dr * dr - dc * dc + 1);
                    nextUnfilled[r][c] = findNext(findNext, r, c + 1);
                    c = nextUnfilled[r][c];
                }
            }
        }

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                if (c) cout << ' ';
                cout << reading[r][c];
            }
            cout << '\n';
        }
    }

    return 0;
}
