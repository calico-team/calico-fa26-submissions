#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct rect {
    int minX, minY, maxX, maxY;
};

struct node {
    rect r;
    array<node *, 4> childs = {};
    int ansIdx = -1;
};

node *root;

node *makeNode(rect r) {
    if (r.maxX < r.minX || r.maxY < r.minY) return nullptr;

    int w = r.maxX - r.minX + 1;
    int h = r.maxY - r.minY + 1;

    bool imbalanced = (w*2 < h || h*2 < w);

    bool divW = (imbalanced && h*2 < w) || (!imbalanced && w > 1);
    bool divH = (imbalanced && w*2 < h) || (!imbalanced && h > 1);

    int midX = (r.minX + r.maxX) / 2;
    int midY = (r.minY + r.maxY) / 2;

    auto n = new node;
    n->r = r;

    if (divW && divH) {
        n->childs[0] = makeNode({r.minX, r.minY, midX, midY});
        n->childs[1] = makeNode({midX + 1, r.minY, r.maxX, midY});
        n->childs[2] = makeNode({r.minX, midY + 1, midX, r.maxY});
        n->childs[3] = makeNode({midX + 1, midY + 1, r.maxX, r.maxY});
    } else if (divW) {
        n->childs[0] = makeNode({r.minX, r.minY, midX, r.maxY});
        n->childs[1] = makeNode({midX + 1, r.minY, r.maxX, r.maxY});
    } else if (divH) {
        n->childs[2] = makeNode({r.minX, r.minY, r.maxX, midY});
        n->childs[3] = makeNode({r.minX, midY + 1, r.maxX, r.maxY});
    }

    return n;
}

ll check(ll x, ll y, ll atX, ll atY, ll atP) {
    return atP * atP - ((x-atX)*(x-atX) + (y-atY)*(y-atY)) + 1;
}

vector<tuple<int, int, int>> qs;
vector<int> ans;
int n, m;

void query(int idx, int x, int y, int r, node *n) {
    if (n == nullptr) {
        return;
    }

    if (n->ansIdx != -1) {
        return;
    }

    ll a = check(n->r.minX, n->r.minY, x, y, r);
    ll b = check(n->r.maxX, n->r.minY, x, y, r);
    ll c = check(n->r.minX, n->r.maxY, x, y, r);
    ll d = check(n->r.maxX, n->r.maxY, x, y, r);

    if (a > 0 && b > 0 && c > 0 && d > 0) {
        n->ansIdx = idx;
        return;
    }

    if (a == 0 && b == 0 && c == 0 && d == 0) {
        return;
    }

    for (int i = 0; i < 4; i++) {
        query(idx, x, y, r, n->childs[i]);
    }
}

void traverse(node *n) {
    if (n == nullptr) {
        return;
    }

    if (n->ansIdx != -1) {
        for (int y = n->r.minY; y <= n->r.maxY; y++) {
            for (int x = n->r.minX;  x<= n->r.maxX; x++) {
                ans[y * m + x] = check(x, y, get<0>(qs[n->ansIdx]), get<1>(qs[n->ansIdx]), get<2>(qs[n->ansIdx]));
            }
        }
    } else {
        for (int i = 0; i < 4; i++) {
            traverse(n->childs[i]);
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int q; cin >> n >> m >> q;
        qs.clear();
        for (int i = 0; i < q; i++) {
            int r, c, p; cin >> r >> c >> p;
            qs.push_back({c, r, p});
        }

        root = makeNode({0, 0, m-1, n-1});

        for (int i = q-1; i >= 0; i--) {
            query(i, get<0>(qs[i]), get<1>(qs[i]), get<2>(qs[i]), root);
        }

        ans.resize(n * m);
        for (int i = 0; i < n*m; i++) ans[i] = 0;
        traverse(root);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << ans[i*m + j] << ' ' ;
            }
            cout << endl;
        }
    }
    return 0;
}