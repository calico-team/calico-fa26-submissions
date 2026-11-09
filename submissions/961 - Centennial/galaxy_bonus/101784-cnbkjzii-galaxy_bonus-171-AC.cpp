#include <bits/stdc++.h>
using namespace std;

vector<int> par, sz;

int findp(int x) {
    while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
    return x;
}

void unite(int a, int b) {
    a = findp(a); b = findp(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a; sz[a] += sz[b];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> g(N);
        for (auto& row : g) cin >> row;
        par.resize(N * M);
        sz.assign(N * M, 1);
        iota(par.begin(), par.end(), 0);
        auto blocked = [](char a, char b) {
            return (a == 'R' && b == 'B') || (a == 'B' && b == 'R');
        };
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (j + 1 < M && !blocked(g[i][j], g[i][j + 1]))
                    unite(i * M + j, i * M + j + 1);
                if (i + 1 < N && !blocked(g[i][j], g[i + 1][j]))
                    unite(i * M + j, (i + 1) * M + j);
            }
        }
        while (Q--) {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            bool ok = findp(r1 * M + c1) == findp(r2 * M + c2);
            cout << (ok ? "YES" : "NO") << '\n';
        }
    }
}