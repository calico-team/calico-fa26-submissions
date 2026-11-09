#include <bits/stdc++.h>
using namespace std;
int p[80005];
int sz[80005];
int find(int x) {
    if (p[x] != x)
        p[x] = find(p[x]);
    return p[x];
}
void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        string g[205];
        for (int i = 0; i < N; i++) {
            cin >> g[i];
        }
        int total = N * M;
        for (int i = 0; i < 2 * total; i++) {
            p[i] = i;
            sz[i] = 1;
        }
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                int blue = r * M + c;
                int red = total + r * M + c;
                if (g[r][c] == '.') {
                    unite(blue, red);
                }
                for (int d = 0; d < 2; d++) {
                    int nr = r + (d == 0);
                    int nc = c + (d == 1);
                    if (nr >= N || nc >= M) continue;
                    int blue2 = nr * M + nc;
                    int red2 = total + nr * M + nc;
                    if (g[r][c] != 'R' && g[nr][nc] != 'R') {
                        unite(blue, blue2);
                    }
                    if (g[r][c] != 'B' && g[nr][nc] != 'B') {
                        unite(red, red2);
                    }
                }
            }
        }
        while (Q--) {
            int rs, cs, re, ce;
            cin >> rs >> cs >> re >> ce;
            int start = rs * M + cs;
            int dest = re * M + ce;
            if (g[re][ce] == 'R') {
                dest += total;
            }
            if (find(start) == find(dest)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    return 0;
}