#include <bits/stdc++.h>
using namespace std;

vector<int> parent, sz;

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b) return;

    if (sz[a] < sz[b]) swap(a, b);

    parent[b] = a;
    sz[a] += sz[b];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> g(N);
        for (int i = 0; i < N; i++)
            cin >> g[i];

        int S = N * M;

        parent.resize(2 * S);
        sz.assign(2 * S, 1);

        for (int i = 0; i < 2 * S; i++)
            parent[i] = i;

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                int id = r * M + c;

                if (g[r][c] == '.')
                    unite(id, id + S);

                for (int mode = 0; mode < 2; mode++) {
                    char blocked = mode == 0 ? 'R' : 'B';

                    if (g[r][c] == blocked)
                        continue;

                    int cur = id + mode * S;

                    if (r > 0 && g[r-1][c] != blocked)
                        unite(cur, id - M + mode * S);

                    if (c > 0 && g[r][c-1] != blocked)
                        unite(cur, id - 1 + mode * S);
                }
            }
        }

        while (Q--) {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;

            int start = r1 * M + c1;
            int target = r2 * M + c2;

            if (g[r2][c2] == 'R')
                target += S;

            cout << (find(start) == find(target) ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}
