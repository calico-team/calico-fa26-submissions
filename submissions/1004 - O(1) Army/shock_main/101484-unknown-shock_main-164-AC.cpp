#include <bits/stdc++.h>
using namespace std;

struct Earthquake { int row, col, power; };

int next_unwritten(vector<int> &parent, int index) {
    int root = index;
    while (parent[root] != root) root = parent[root];
    while (parent[index] != index) {
        int next = parent[index];
        parent[index] = root;
        index = next;
    }
    return root;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    while (tests--) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<Earthquake> events(q);
        for (auto &[row, col, power] : events) cin >> row >> col >> power;
        // Transpose the calculation to sweep along the shorter dimension.
        bool transpose = n > m;
        int rows = min(n, m), cols = max(n, m);
        vector<int> result(n * m);
        vector<int> parent(rows * (cols + 1));
        iota(parent.begin(), parent.end(), 0);
        for (auto it = events.rbegin(); it != events.rend(); ++it) {
            auto [row, col, power] = *it;
            if (transpose) swap(row, col);
            for (int r = row - power; r <= row + power; ++r) {
                int dy = r - row;
                int remaining = power * power - dy * dy;
                int radius = int(sqrt(remaining));
                int offset = r * (cols + 1);
                int end = offset + col + radius;
                for (int index = next_unwritten(parent, offset + col - radius);
                     index <= end; index = parent[index]) {
                    int c = index - offset;
                    int dx = c - col;
                    result[transpose ? c * m + r : r * m + c] = remaining - dx * dx + 1;
                    parent[index] = next_unwritten(parent, index + 1);
                }
            }
        }
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < m; ++c)
                cout << result[r * m + c] << (c + 1 == m ? '\n' : ' ');
    }
}
