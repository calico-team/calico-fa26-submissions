#include <bits/stdc++.h>
using namespace std;
struct Earthquake {
    int r, c, p;
};
int findNext(vector<int>& parent, int x) {
    int root = x;
    while (parent[root] != root) root = parent[root];
    while (parent[x] != x) {
        int next = parent[x];
        parent[x] = root;
        x = next;
    }
    return root;
}
int integerSqrt(int value) {
    int x = static_cast<int>(sqrt(static_cast<double>(value)));
    while (1LL * (x + 1) * (x + 1) <= value) ++x;
    while (1LL * x * x > value) --x;
    return x;
}
int main() {
    int T, N, M, Q;
    cin >> T;
    while (T--) {
        cin >> N >> M >> Q;
        vector<Earthquake> earthquakes(Q);
        for (int i = 0; i < Q; ++i) {
            cin >> earthquakes[i].r;
            cin >> earthquakes[i].c;
            cin >> earthquakes[i].p;
        }
        vector<int> answer(N * M, 0);
        int width = M + 1, i, c, dc;
        vector<int> parent(N * width);
        iota(parent.begin(), parent.end(), 0);
        for (i = Q - 1; i >= 0; --i) {
            int R = earthquakes[i].r, C = earthquakes[i].c, P = earthquakes[i].p, powerSquared = P * P;
            for (int r = R - P; r <= R + P; ++r) {
                int dr = r - R, remaining = powerSquared - dr * dr, x = integerSqrt(remaining);
                int left = C - x, right = C + x, rowBase = r * width, pos = findNext(parent, rowBase + left);
                while (pos <= rowBase + right) {
                    c = pos - rowBase, dc = c - C;
                    answer[r * M + c] =
                        powerSquared - dr * dr - dc * dc + 1;
                    parent[pos] = findNext(parent, pos + 1);
                    pos = findNext(parent, pos);
                }
            }
        }
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                if (c > 0) cout << ' ';
                cout << answer[r * M + c];
            }
            cout << '\n';
        }
    }
    return 0;
}