#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll f = 1e18; // infinity definition

// matrix data structure for column transitions
struct m_t {
    int s;
    vector<vector<ll>> a;
    m_t(int sz = 0) : s(sz), a(sz, vector<ll>(sz, f)) {
        for (int i = 0; i < sz; ++i) a[i][i] = 0;
    }
};

// combine two distance matrices using tropical matrix multiplication
m_t mul(const m_t& x, const m_t& y) {
    int sz = x.s;
    m_t z(sz);
    for (int i = 0; i < sz; ++i) {
        for (int k = 0; k < sz; ++k) {
            if (x.a[i][k] == f) continue;
            for (int j = 0; j < sz; ++j) {
                if (y.a[k][j] == f) continue;
                z.a[i][j] = min(z.a[i][j], x.a[i][k] + y.a[k][j]);
            }
        }
    }
    return z;
}

void solve() {
    int n, m, q;
    if (!(cin >> n >> m >> q)) return;

    vector<string> g(n);
    for (int i = 0; i < n; ++i) cin >> g[i];

    auto ok = [&](int r, int c, int md) {
        char ch = g[r][c];
        if (ch == '.') return true;
        return (ch == 'B') == (md == 0);
    };

    int sz = 2 * n;
    vector<m_t> tree(4 * m);

    // build segment tree over columns
    function<void(int, int, int)> build = [&](int node, int l, int r) {
        if (l == r) {
            m_t d(sz);
            for (int i = 0; i < sz; ++i) {
                for (int j = 0; j < sz; ++j) d.a[i][j] = f;
                d.a[i][i] = 0;
            }

            for (int i = 0; i < sz; ++i) {
                priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
                vector<ll> dist(sz, f);
                dist[i] = 0;
                pq.push({0, i});

                while (!pq.empty()) {
                    auto [w, u] = pq.top();
                    pq.pop();
                    if (w > dist[u]) continue;

                    int ur = u / 2, um = u % 2;
                    // toggle mode on normal tile takes 1s
                    if (g[ur][l] == '.' && dist[u ^ 1] > dist[u] + 1) {
                        dist[u ^ 1] = dist[u] + 1;
                        pq.push({dist[u ^ 1], u ^ 1});
                    }

                    int dr[] = {1, -1, 0, 0};
                    int dc[] = {0, 0, 1, -1};
                    for (int d_idx = 0; d_idx < 4; ++d_idx) {
                        int nr = ur + dr[d_idx];
                        int nc = l + dc[d_idx];
                        // vertical movement within the same column
                        if (nc == l && nr >= 0 && nr < n && ok(nr, l, um)) {
                            int v = nr * 2 + um;
                            if (dist[v] > dist[u] + 1) {
                                dist[v] = dist[u] + 1;
                                pq.push({dist[v], v});
                            }
                        }
                    }
                }
                for (int j = 0; j < sz; ++j) d.a[i][j] = dist[j];
            }

            if (l < m - 1) {
                m_t trans(sz);
                for (int i = 0; i < sz; ++i) {
                    for (int j = 0; j < sz; ++j) trans.a[i][j] = f;
                }
                for (int u = 0; u < sz; ++u) {
                    int ur = u / 2, um = u % 2;
                    for (int w = 0; w < sz; ++w) {
                        int wr = w / 2, wm = w % 2;
                        // moving horizontally to column l + 1 takes 1s
                        if (wr == ur && wm == um && ok(ur, l, um) && ok(ur, l + 1, um)) {
                            for (int v = 0; v < sz; ++v) {
                                trans.a[u][v] = min(trans.a[u][v], d.a[u][w] + 1);
                            }
                        }
                    }
                }
                tree[node] = trans;
            } else {
                tree[node] = d;
            }
            return;
        }

        int mid = (l + r) / 2;
        build(2 * node, l, mid);
        build(2 * node + 1, mid + 1, r);
        if (l < m - 1) {
            tree[node] = mul(tree[2 * node], tree[2 * node + 1]);
        } else {
            tree[node] = tree[2 * node];
        }
    };

    if (m > 1) {
        build(1, 0, m - 1);
    } else {
        m_t d(sz);
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) d.a[i][j] = f;
            d.a[i][i] = 0;
        }
        for (int i = 0; i < sz; ++i) {
            priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
            vector<ll> dist(sz, f);
            dist[i] = 0;
            pq.push({0, i});
            while (!pq.empty()) {
                auto [w, u] = pq.top();
                pq.pop();
                if (w > dist[u]) continue;
                int ur = u / 2, um = u % 2;
                if (g[ur][0] == '.' && dist[u ^ 1] > dist[u] + 1) {
                    dist[u ^ 1] = dist[u] + 1;
                    pq.push({dist[u ^ 1], u ^ 1});
                }
                int dr[] = {1, -1};
                for (int d_idx = 0; d_idx < 2; ++d_idx) {
                    int nr = ur + dr[d_idx];
                    if (nr >= 0 && nr < n && ok(nr, 0, um)) {
                        int v = nr * 2 + um;
                        if (dist[v] > dist[u] + 1) {
                            dist[v] = dist[u] + 1;
                            pq.push({dist[v], v});
                        }
                    }
                }
            }
            for (int j = 0; j < sz; ++j) d.a[i][j] = dist[j];
        }
        tree[1] = d;
    }

    // query range over segment tree
    function<m_t(int, int, int, int, int)> query = [&](int node, int l, int r, int ql, int qr) -> m_t {
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        if (qr <= mid) return query(2 * node, l, mid, ql, qr);
        if (ql > mid) return query(2 * node + 1, mid + 1, r, ql, qr);
        return mul(query(2 * node, l, mid, ql, qr), query(2 * node + 1, mid + 1, r, ql, qr));
    };

    while (q--) {
        int r1, c1, r2, c2;
        ll lim;
        cin >> r1 >> c1 >> r2 >> c2 >> lim;

        int s = r1 * 2 + 0; // start in blue mode (mode 0)[cite: 23]
        ll ans = f;

        if (c1 <= c2) {
            if (c1 == c2) {
                m_t mat = query(1, 0, m - 1, c1, c1);
                for (int m_idx = 0; m_idx < 2; ++m_idx) {
                    int e = r2 * 2 + m_idx;
                    ans = min(ans, mat.a[s][e]);
                }
            } else {
                m_t mat = query(1, 0, m - 1, c1, c2 - 1);
                for (int m_idx = 0; m_idx < 2; ++m_idx) {
                    int e = r2 * 2 + m_idx;
                    ans = min(ans, mat.a[s][e]);
                }
            }
        } else {
            m_t mat = query(1, 0, m - 1, c2, c1 - 1);
            for (int m_idx = 0; m_idx < 2; ++m_idx) {
                int e = r1 * 2 + m_idx;
                ans = min(ans, mat.a[e][r2 * 2 + 0]);
            }
        }

        if (ans <= lim) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}