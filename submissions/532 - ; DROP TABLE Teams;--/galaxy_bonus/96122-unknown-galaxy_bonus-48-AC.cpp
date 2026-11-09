#include<bits/stdc++.h>
#include <pthread.h>
using namespace std;
#define int long long
#define all(x) x.begin(), x.end()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
#define vi vector<int>
#define si set<int>
#define vvi vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pair<int, int>>

struct DSU {
    int n;
    vi head, sz;
    DSU (int n) : n(n), head(n), sz(n, 1) {iota(all(head), 0ll);};
    int find(int u) { return u == head[u] ? u : head[u] = find(head[u]); }
    void join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v)
            return;
        if (sz[u] < sz[v])
            swap(u, v);
        head[v] = u;
        sz[u] += sz[v];
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<string> ggrid(n);
        vi adj = {1, -1, m, -m};

        rep(i, 0, n)
            cin >> ggrid[i];
        vector<char> grid(n * m);
        rep(i, 0, n)
            rep(j, 0, m)
            grid[i * m + j] = ggrid[i][j];
        vi vis(n * m);
        DSU dsu(n * m);
        rep(i, 0, n) {
            rep(j, 0, m) {
                int cur = i * m + j;
                if (vis[cur])
                    continue;
                queue<int> q;
                q.push(cur);
                while (q.size()) {
                    int ccur = q.front();
                    q.pop();
                    if (vis[ccur])
                        continue;
                    vis[ccur] = 1;
                    dsu.join(cur, ccur);
                    // go right/left
                    int cccur = ccur + 1;
                    if (cccur % m && cccur < n * m && cccur >= 0) {
                        if (grid[cccur] == '.' || grid[ccur] == '.' || grid[ccur] == grid[cccur])
                            q.push(cccur);
                    }
                    cccur = ccur - 1;
                    if (ccur % m && cccur < n * m && cccur >= 0) {
                        if (grid[cccur] == '.' || grid[ccur] == '.' || grid[ccur] == grid[cccur])
                            q.push(cccur);
                    }
                    // go up down
                    cccur = ccur - m;
                    if (cccur < n * m && cccur >= 0) {
                        if (grid[cccur] == '.' || grid[ccur] == '.' || grid[ccur] == grid[cccur])
                            q.push(cccur);
                    }
                    cccur = ccur + m;
                    if (cccur < n * m && cccur >= 0) {
                        if (grid[cccur] == '.' || grid[ccur] == '.' || grid[ccur] == grid[cccur])
                            q.push(cccur);
                    }
                }
            }
        }
        while (q--) {
            int sx, sy, ex, ey;
            cin >> sx >> sy >> ex >> ey;
            cout << (dsu.find(sx * m + sy) == dsu.find(ex * m + ey) ? "YES" : "NO") << endl;
        }
    }
}
