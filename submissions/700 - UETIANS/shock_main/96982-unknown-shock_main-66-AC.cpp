#include <bits/stdc++.h>
using namespace std;

// DSU "next" - har row ke liye alag
struct NextDSU {
    vector<vector<int>> p;
    NextDSU() {}
    NextDSU(int n, int m) { init(n, m); }
    void init(int n, int m) {
        p.assign(n, vector<int>(m + 1));
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= m; j++)
                p[i][j] = j;
    }
    int find(int r, int x) {
        auto &row = p[r];
        int root = x;
        while (row[root] != root) root = row[root];
        while (row[x] != x) {
            int nxt = row[x];
            row[x] = root;
            x = nxt;
        }
        return root;
    }
    void erase(int r, int x) {
        p[r][x] = find(r, x + 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<int> R(Q), C(Q), P(Q);
        for (int i = 0; i < Q; i++) cin >> R[i] >> C[i] >> P[i];

        vector<vector<int>> ans(N, vector<int>(M, 0));
        NextDSU dsu(N, M);
        int remaining = N * M;

        // reverse me - aakhri earthquake pehle
        for (int qi = Q - 1; qi >= 0 && remaining > 0; qi--) {
            int Ri = R[qi], Ci = C[qi], Pi = P[qi];
            int p2 = Pi * Pi;
            for (int dr = -Pi; dr <= Pi; dr++) {
                int r = Ri + dr;
                int rem = p2 - dr * dr;
                int dy = (int)sqrt((double)rem);
                while ((dy + 1) * (dy + 1) <= rem) dy++;
                while (dy * dy > rem) dy--;
                int l = Ci - dy;
                int rr = Ci + dy;
                int c = dsu.find(r, l);
                while (c <= rr) {
                    int dc = c - Ci;
                    int dist2 = dr * dr + dc * dc;
                    ans[r][c] = p2 - dist2 + 1;
                    dsu.erase(r, c);
                    remaining--;
                    c = dsu.find(r, c); // agla unassigned, yehi skip hai
                }
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (j) cout << ' ';
                cout << ans[i][j];
            }
            if (T || i + 1 < N) cout << '\n';
        }
    }
    return 0;
}