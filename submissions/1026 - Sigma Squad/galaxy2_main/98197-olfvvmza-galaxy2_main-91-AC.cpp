#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n, m;
vector<string> g;
vector<int> qa, qb, qc, qd, best;
vector<int> dist, que;

bool ok(int r, int c, int k) {
    char ch = g[r][c];
    if (ch == '.') return true;
    if (k == 0) return ch == 'B';
    return ch == 'R';
}

int id(int r, int c, int k) {
    return (c * n + r) * 2 + k;
}

void bfs(int sr, int sc, int sk, int l, int r) {
    for (int i = l * n * 2; i < (r + 1) * n * 2; i++) dist[i] = INF;
    int h = 0, tl = 0;
    dist[id(sr, sc, sk)] = 0;
    que[tl++] = id(sr, sc, sk);
    int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
    while (h < tl) {
        int u = que[h++];
        int k = u % 2, x = (u / 2) % n, y = (u / 2) / n;
        int d = dist[u];
        if (g[x][y] == '.') {
            int v = id(x, y, 1 - k);
            if (dist[v] == INF) {
                dist[v] = d + 1;
                que[tl++] = v;
            }
        }
        for (int i = 0; i < 4; i++) {
            int a = x + dr[i], b = y + dc[i];
            if (a < 0 || a >= n || b < l || b > r) continue;
            if (!ok(a, b, k)) continue;
            int v = id(a, b, k);
            if (dist[v] == INF) {
                dist[v] = d + 1;
                que[tl++] = v;
            }
        }
    }
}

void solve(int l, int r, vector<int> &qs) {
    if (l > r || qs.empty()) return;
    int mid = (l + r) / 2;
    for (int row = 0; row < n; row++) {
        for (int k = 0; k < 2; k++) {
            if (!ok(row, mid, k)) continue;
            bfs(row, mid, k, l, r);
            for (int q : qs) {
                int ds = dist[id(qa[q], qb[q], 0)];
                int dt = min(dist[id(qc[q], qd[q], 0)], dist[id(qc[q], qd[q], 1)]);
                if (ds < INF && dt < INF) best[q] = min(best[q], ds + dt);
            }
        }
    }
    vector<int> L, R;
    for (int q : qs) {
        if (qb[q] < mid && qd[q] < mid) L.push_back(q);
        else if (qb[q] > mid && qd[q] > mid) R.push_back(q);
    }
    qs.clear();
    qs.shrink_to_fit();
    solve(l, mid - 1, L);
    solve(mid + 1, r, R);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int q;
        cin >> n >> m >> q;
        g.assign(n, "");
        for (int i = 0; i < n; i++) cin >> g[i];
        qa.assign(q, 0); qb.assign(q, 0); qc.assign(q, 0); qd.assign(q, 0);
        best.assign(q, INF);
        vector<long long> K(q);
        for (int i = 0; i < q; i++) cin >> qa[i] >> qb[i] >> qc[i] >> qd[i] >> K[i];
        dist.assign(n * m * 2, INF);
        que.assign(n * m * 2, 0);
        vector<int> all(q);
        iota(all.begin(), all.end(), 0);
        solve(0, m - 1, all);
        for (int i = 0; i < q; i++) {
            if (best[i] < INF && best[i] <= K[i]) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}
