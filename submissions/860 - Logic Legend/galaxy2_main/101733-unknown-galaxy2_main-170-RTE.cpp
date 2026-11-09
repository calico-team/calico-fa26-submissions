// Source: https://usaco.guide/general/io
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Node {
    int len;
    vector<int> d;

    Node() : len(0) {}

    explicit Node(int length) : len(length), d(400, INF) {}
};

Node mergeNodes(const Node& a, const Node& b, int s) {
    if (a.len == 0) return b;
    if (b.len == 0) return a;

    int total = 3 * s;
    vector<int> d(total * total, INF);

    auto at = [total, &d](int i, int j) -> int& {
        return d[i * total + j];
    };

    for (int i = 0; i < 2 * s; ++i) {
        for (int j = 0; j < 2 * s; ++j) {
            at(i, j) = a.d[i * (2 * s) + j];
        }
    }

    for (int i = 0; i < 2 * s; ++i) {
        for (int j = 0; j < 2 * s; ++j) {
            at(s + i, s + j) = b.d[i * (2 * s) + j];
        }
    }

    for (int k = 0; k < total; ++k) {
        for (int i = 0; i < total; ++i) {
            int dik = at(i, k);
            if (dik >= INF) continue;

            for (int j = 0; j < total; ++j) {
                int dkj = at(k, j);
                if (dkj < INF && dik + dkj < at(i, j)) {
                    at(i, j) = dik + dkj;
                }
            }
        }
    }

    Node result(a.len + b.len);

    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < s; ++j) {
            result.d[i * (2 * s) + j] = at(i, j);
            result.d[i * (2 * s) + (s + j)] = at(i, 2 * s + j);
            result.d[(s + i) * (2 * s) + j] = at(2 * s + i, j);
            result.d[(s + i) * (2 * s) + (s + j)] = at(2 * s + i, 2 * s + j);
        }
    }

    return result;
}

Node makeLeaf(const string& column, int n) {
    int s = 2 * n;
    Node node(1);

    for (int r = 0; r < n; ++r) {
        for (int mode = 0; mode < 2; ++mode) {
            int u = 2 * r + mode;
            node.d[u * s + u] = 0;

            if (column[r] == '.') {
                int v = 2 * r + (1 - mode);
                node.d[u * s + v] = 1;
            }

            if (r + 1 < n) {
                char tile = column[r + 1];
                int nextMode = mode;

                if ((tile == 'R' && mode == 0) ||
                    (tile == 'B' && mode == 1) ||
                    tile == '.') {
                    int v = 2 * (r + 1) + nextMode;
                    node.d[u * s + v] = 1;
                }
            }
        }
    }

    for (int r = 0; r < n; ++r) {
        for (int mode = 0; mode < 2; ++mode) {
            int u = 2 * r + mode;

            if (r > 0) {
                char tile = column[r - 1];

                if ((tile == 'R' && mode == 0) ||
                    (tile == 'B' && mode == 1) ||
                    tile == '.') {
                    int v = 2 * (r - 1) + mode;
                    node.d[u * s + v] = 1;
                }
            }
        }
    }

    for (int k = 0; k < s; ++k) {
        for (int i = 0; i < s; ++i) {
            int dik = node.d[i * s + k];
            if (dik >= INF) continue;

            for (int j = 0; j < s; ++j) {
                int dkj = node.d[k * s + j];
                if (dkj < INF && dik + dkj < node.d[i * s + j]) {
                    node.d[i * s + j] = dik + dkj;
                }
            }
        }
    }

    return node;
}

struct SegmentTree {
    int n;
    int s;
    vector<Node> tree;

    SegmentTree(const vector<string>& grid, int rows, int cols)
        : n(cols), s(2 * rows), tree(4 * cols) {
        build(1, 0, n - 1, grid, rows);
    }

    void build(int v, int l, int r, const vector<string>& grid, int rows) {
        if (l == r) {
            string column(rows, '.');
            for (int i = 0; i < rows; ++i) {
                column[i] = grid[i][l];
            }
            tree[v] = makeLeaf(column, rows);
            return;
        }

        int mid = (l + r) / 2;
        build(v * 2, l, mid, grid, rows);
        build(v * 2 + 1, mid + 1, r, grid, rows);
        tree[v] = mergeNodes(tree[v * 2], tree[v * 2 + 1], s);
    }

    Node query(int v, int l, int r, int ql, int qr) const {
        if (ql <= l && r <= qr) return tree[v];

        int mid = (l + r) / 2;

        if (qr <= mid) return query(v * 2, l, mid, ql, qr);
        if (ql > mid) return query(v * 2 + 1, mid + 1, r, ql, qr);

        Node left = query(v * 2, l, mid, ql, qr);
        Node right = query(v * 2 + 1, mid + 1, r, ql, qr);
        return mergeNodes(left, right, s);
    }

    Node query(int l, int r) const {
        return query(1, 0, n - 1, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> grid(N);
        for (int r = 0; r < N; ++r) {
            cin >> grid[r];
        }

        SegmentTree seg(grid, N, M);

        while (Q--) {
            int rs, cs, re, ce;
            long long k;
            cin >> rs >> cs >> re >> ce >> k;

            int left = min(cs, ce);
            int right = max(cs, ce);
            Node result = seg.query(left, right);
            int s = 2 * N;

            int startRow = rs;
            int endRow = re;

            if (cs <= ce) {
                int startState = 2 * startRow + 1;
                int endBlue = 2 * endRow;
                int endRed = endBlue + 1;

                int d1 = result.d[startState * s + endBlue];
                int d2 = result.d[startState * s + endRed];
                int best = min(d1, d2);

                cout << (best <= k ? "YES\n" : "NO\n");
            } else {
                int startState = 2 * startRow + 1;
                int endBlue = 2 * endRow;
                int endRed = endBlue + 1;

                int d1 = result.d[(s + startState) * s + endBlue];
                int d2 = result.d[(s + startState) * s + endRed];
                int best = min(d1, d2);

                cout << (best <= k ? "YES\n" : "NO\n");
            }
        }
    }

    return 0;
}

