
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Node {
    int l, r, mid;
    int left = -1, right = -1;
    vector<int> dist;
};

int n, m, W;
vector<string> g;
vector<vector<int>> adj;
vector<Node> tree;

int id(int r, int c, int state) {
    return c * W + state;
}

int build(int l, int r) {
    int idx = (int)tree.size();
    tree.emplace_back();

    tree[idx].l = l;
    tree[idx].r = r;
    tree[idx].mid = (l + r) / 2;

    int mid = tree[idx].mid;
    int len = r - l + 1;

    tree[idx].dist.assign(W * len * W, INF);

    for (int s = 0; s < W; s++) {
        int base = s * len * W;
        int start = id(0, mid, s);

        vector<int> que;
        que.reserve(len * W);

        tree[idx].dist[base + (mid - l) * W + s] = 0;
        que.push_back(start);

        int head = 0;

        while (head < (int)que.size()) {
            int u = que[head++];
            int col = u / W;
            int state = u % W;

            int cur = base + (col - l) * W + state;
            int nd = tree[idx].dist[cur] + 1;

            for (int v : adj[u]) {
                int vc = v / W;

                if (vc < l || vc > r)
                    continue;

                int vs = v % W;
                int pos = base + (vc - l) * W + vs;

                if (tree[idx].dist[pos] == INF) {
                    tree[idx].dist[pos] = nd;
                    que.push_back(v);
                }
            }
        }
    }

    if (l < mid)
        tree[idx].left = build(l, mid - 1);

    if (mid < r)
        tree[idx].right = build(mid + 1, r);

    return idx;
}

int getDistance(int idx, int c1, int s1, int c2, int s2) {
    Node &nd = tree[idx];

    int len = nd.r - nd.l + 1;
    int answer = INF;

    for (int s = 0; s < W; s++) {
        int base = s * len * W;

        int d1 = nd.dist[base + (c1 - nd.l) * W + s1];
        int d2 = nd.dist[base + (c2 - nd.l) * W + s2];

        if (d1 != INF && d2 != INF)
            answer = min(answer, d1 + d2);
    }

    return answer;
}

int query(int c1, int s1, int c2, int s2) {
    int idx = 0;
    int answer = INF;

    while (idx != -1) {
        Node &nd = tree[idx];

        answer = min(
            answer,
            getDistance(idx, c1, s1, c2, s2)
        );

        int mid = nd.mid;

        if (c1 == mid || c2 == mid)
            break;

        if (c1 < mid && c2 < mid)
            idx = nd.left;
        else if (c1 > mid && c2 > mid)
            idx = nd.right;
        else
            break;
    }

    return answer;
}

void solve() {
    int q;
    cin >> n >> m >> q;

    g.resize(n);

    for (int i = 0; i < n; i++)
        cin >> g[i];

    W = 2 * n;

    adj.assign(m * W, {});

    auto active = [&](int r, int c, int mode) {
        char ch = g[r][c];

        if (ch == '.') return true;
        if (ch == 'B') return mode == 0;

        return mode == 1;
    };

    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    for (int c = 0; c < m; c++) {
        for (int r = 0; r < n; r++) {
            for (int mode = 0; mode < 2; mode++) {
                if (!active(r, c, mode))
                    continue;

                int state = mode * n + r;
                int u = id(r, c, state);

                if (r + 1 < n && active(r + 1, c, mode))
                    addEdge(u, id(r + 1, c, state + 1));

                if (c + 1 < m && active(r, c + 1, mode))
                    addEdge(u, id(r, c + 1, state));
            }

            if (g[r][c] == '.') {
                addEdge(
                    id(r, c, r),
                    id(r, c, n + r)
                );
            }
        }
    }

    tree.clear();
    tree.reserve(2 * m);

    build(0, m - 1);

    while (q--) {
        int rs, cs, re, ce;
        long long k;

        cin >> rs >> cs >> re >> ce >> k;

        int startState = rs;
        int answer = INF;

        if (g[re][ce] == '.') {
            answer = min(
                query(cs, startState, ce, re),
                query(cs, startState, ce, n + re)
            );
        }
        else if (g[re][ce] == 'B') {
            answer = query(cs, startState, ce, re);
        }
        else {
            answer = query(cs, startState, ce, n + re);
        }

        cout << (answer <= k ? "YES" : "NO") << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
        solve();

    return 0;
}
