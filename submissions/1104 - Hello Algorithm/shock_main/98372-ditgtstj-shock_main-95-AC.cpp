#include <bits/stdc++.h>
using namespace std;

struct Earthquake {
    int r, c, p;
};

vector<int> parent;

int find(int x) {
    int root = x;

    while (parent[root] != root)
        root = parent[root];

    while (parent[x] != x) {
        int next = parent[x];
        parent[x] = root;
        x = next;
    }

    return root;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<Earthquake> eq(Q);

        for (int i = 0; i < Q; i++)
            cin >> eq[i].r >> eq[i].c >> eq[i].p;

        vector<vector<int>> ans(N, vector<int>(M, 0));

        int width = M + 1;
        parent.resize(N * width);
        iota(parent.begin(), parent.end(), 0);

        int remaining = N * M;

        for (int i = Q - 1; i >= 0 && remaining > 0; i--) {
            int R = eq[i].r;
            int C = eq[i].c;
            int P = eq[i].p;
            int P2 = P * P;

            for (int r = R - P; r <= R + P; r++) {
                int dr = r - R;
                int d = (int)sqrt(P2 - dr * dr);

                int left = C - d;
                int right = C + d;
                int base = r * width;

                int pos = find(base + left);

                while (pos <= base + right) {
                    int c = pos - base;
                    int dc = c - C;

                    ans[r][c] = P2 - dr * dr - dc * dc + 1;
                    remaining--;

                    parent[pos] = find(pos + 1);
                    pos = find(pos);
                }
            }
        }

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                if (c) cout << ' ';
                cout << ans[r][c];
            }
            cout << '\n';
        }
    }

    return 0;
}
