#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> g(N);
        for (int i = 0; i < N; ++i) cin >> g[i];

        int S = N * M * 2;
        vector<int> comp(S, -1);
        vector<int> q(S);
        int cid = 0;

        for (int i = 0; i < S; ++i) {
            if (comp[i] != -1) continue;
            int r = i / (2 * M), c = (i / 2) % M, md = i % 2;

            char ch = g[r][c];
            if (ch != '.' && ((ch == 'B') != (md == 0))) continue;

            int h = 0, t = 0;
            q[t++] = i;
            comp[i] = cid;

            while (h < t) {
                int u = q[h++];
                int cr = u / (2 * M), cc = (u / 2) % M, cm = u % 2;

                if (g[cr][cc] == '.') {
                    int alt = u ^ 1;
                    if (comp[alt] == -1) {
                        comp[alt] = cid;
                        q[t++] = alt;
                    }
                }

                int dr[] = {0, 0, 1, -1};
                int dc[] = {1, -1, 0, 0};
                for (int d = 0; d < 4; ++d) {
                    int nr = cr + dr[d], nc = cc + dc[d];
                    if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                        char nch = g[nr][nc];
                        if (nch == '.' || ((nch == 'B') == (cm == 0))) {
                            int v = (nr * M + nc) * 2 + cm;
                            if (comp[v] == -1) {
                                comp[v] = cid;
                                q[t++] = v;
                            }
                        }
                    }
                }
            }
            cid++;
        }

        while (Q--) {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;

            int u = (r1 * M + c1) * 2; // Ben starts in blue mode (mode 0)[cite: 6]
            int v0 = (r2 * M + c2) * 2;     // Destination mode 0 (blue)
            int v1 = v0 + 1;                // Destination mode 1 (red)

            if (comp[u] != -1 && (comp[u] == comp[v0] || comp[u] == comp[v1])) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    return 0;
}