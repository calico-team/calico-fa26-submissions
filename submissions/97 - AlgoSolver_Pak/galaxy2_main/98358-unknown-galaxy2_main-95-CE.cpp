#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> g(N);
        for (int i = 0; i < N; i++) cin >> g[i];

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        for (int qq = 0; qq < Q; qq++) {
            int rs, cs, re, ce;
            long long K;
            cin >> rs >> cs >> re >> ce >> K;

            int dist[10][4000][2];
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    dist[i][j][0] = dist[i][j][1] = -1;

            queue<int> q;
            dist[rs][cs][0] = 0;
            q.push(rs * 100000 + cs * 2 + 0);

            while (!q.empty()) {
                int cur = q.front(); q.pop();
                int mode = cur % 2;
                int c = (cur / 2) % 4000;
                int r = (cur / 2) / 4000;
                if (r < 0 || r >= N || c < 0 || c >= M) continue;
                int d = dist[r][c][mode];

                if (g[r][c] == '.' && dist[r][c][mode ^ 1] == -1) {
                    dist[r][c][mode ^ 1] = d + 1;
                    q.push(r * 100000 + c * 2 + (mode ^ 1));
                }
                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k], nc = c + dc[k];
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
                    if (dist[nr][nc][mode] != -1) continue;
                    char ch = g[nr][nc];
                    if (ch == '.' || (mode == 0 && ch == 'B') || (mode == 1 && ch == 'R')) {
                        dist[nr][nc][mode] = d + 1;
                        q.push(nr * 100000 + nc * 2 + mode);
                    }
                }
            }

            int best = 1e9;
            for (int m = 0; m < 2; m++)
                if (dist[re][ce][m] != -1) best = min(best, dist[re][ce][m]);

            if (best <= K && (K - best) % 2 == 0) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}