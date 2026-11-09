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

        vector<Earthquake> events(Q);
        int maxP = 0;
        for (auto &e : events) {
            cin >> e.r >> e.c >> e.p;
            maxP = max(maxP, e.p);
        }

        // reach[p][dy] is the largest horizontal offset in a
        // radius-p circle at vertical offset dy.
        vector<vector<int>> reach(maxP + 1);
        for (int p = 0; p <= maxP; ++p) {
            reach[p].resize(p + 1);
            int dx = p;
            for (int dy = 0; dy <= p; ++dy) {
                while (dx * dx + dy * dy > p * p) --dx;
                reach[p][dy] = dx;
            }
        }

        vector<int> answer(N * M, 0);

        // Each row has its own successor DSU, including a sentinel at M.
        // Successors point to the first column not assigned yet.
        vector<int> nextCell(N * (M + 1));
        iota(nextCell.begin(), nextCell.end(), 0);

        auto findNext = [&](int x) -> int {
            int root = x;
            while (nextCell[root] != root) root = nextCell[root];
            while (nextCell[x] != x) {
                int t = nextCell[x];
                nextCell[x] = root;
                x = t;
            }
            return root;
        };

        // The latest earthquake affecting a block determines its final value.
        for (int i = Q - 1; i >= 0; --i) {
            const auto &[R, C, P] = events[i];
            int p2 = P * P;

            for (int dy = -P; dy <= P; ++dy) {
                int r = R + dy;
                int dxMax = reach[P][abs(dy)];
                int left = C - dxMax;
                int right = C + dxMax;

                int rowBase = r * (M + 1);
                int pos = findNext(rowBase + left);

                while (pos <= rowBase + right) {
                    int c = pos - rowBase;
                    int dx = c - C;
                    answer[r * M + c] = p2 - dy * dy - dx * dx + 1;

                    nextCell[pos] = findNext(pos + 1);
                    pos = nextCell[pos];
                }
            }
        }

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                if (c) cout << ' ';
                cout << answer[r * M + c];
            }
            cout << '\n';
        }
    }
    return 0;
}
