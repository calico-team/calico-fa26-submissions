#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int N, M, Q; cin >> N >> M >> Q;
        vector<string> G(N);
        for (auto &s : G) cin >> s;
        vector<int> P(2 * N * M);
        iota(P.begin(), P.end(), 0);
        auto Find = [&](int x) {
            while (P[x] != x) x = P[x] = P[P[x]];
            return x;
        };
        auto On = [&](int r, int c, int m) { return G[r][c] == '.' || G[r][c] == "BR"[m]; };
        for (int r = 0; r < N; r++)
            for (int c = 0; c < M; c++) {
                if (G[r][c] == '.') P[Find((r * M + c) * 2)] = Find((r * M + c) * 2 + 1);
                for (int m = 0; m < 2; m++) {
                    if (!On(r, c, m)) continue;
                    if (r + 1 < N && On(r + 1, c, m)) P[Find((r * M + c) * 2 + m)] = Find(((r + 1) * M + c) * 2 + m);
                    if (c + 1 < M && On(r, c + 1, m)) P[Find((r * M + c) * 2 + m)] = Find((r * M + c + 1) * 2 + m);
                }
            }
        while (Q--) {
            int a, b, c, d; cin >> a >> b >> c >> d;
            cout << (Find((a * M + b) * 2) == Find((c * M + d) * 2 + (G[c][d] == 'R')) ? "YES" : "NO") << '\n';
        }
    }
}