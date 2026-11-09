#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 1e9;
int n;
vector<string> *g;
vector<int> sx, sy, ex, ey;
vector<ll> ans;

bool ok(int x, int y, int m) {
    char c = (*g)[x][y];
    if (c == '.') return 1;
    return c == 'B' ? m == 0 : m == 1;
}

void go(int l, int r, vector<int> &qs) {
    if (qs.empty()) return;
    int mid = (l + r) / 2, S = (r - l + 1) * n * 2;
    {
        vector<int> d(2 * n * S, INF), q(S);
        auto id = [&](int x, int y, int m) { return ((y - l) * n + x) * 2 + m; };
        for (int i = 0; i < n; i++) for (int m = 0; m < 2; m++) {
            if (!ok(i, mid, m)) continue;
            int *D = &d[(i * 2 + m) * S];
            int h = 0, t = 0;
            D[id(i, mid, m)] = 0;
            q[t++] = id(i, mid, m);
            while (h < t) {
                int u = q[h++];
                int md = u & 1, cell = u >> 1;
                int x = cell % n, y = cell / n + l;
                int nd = D[u] + 1;
                int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
                for (int k = 0; k < 4; k++) {
                    int a = x + dx[k], b = y + dy[k];
                    if (a < 0 || a >= n || b < l || b > r || !ok(a, b, md)) continue;
                    int v = id(a, b, md);
                    if (D[v] > nd) D[v] = nd, q[t++] = v;
                }
                if ((*g)[x][y] == '.' && D[u ^ 1] > nd) D[u ^ 1] = nd, q[t++] = u ^ 1;
            }
        }
        for (int i : qs) {
            int a = id(sx[i], sy[i], 0);
            int b0 = id(ex[i], ey[i], 0), b1 = id(ex[i], ey[i], 1);
            for (int s = 0; s < 2 * n; s++) {
                int *D = &d[s * S];
                int u = D[a], v = min(D[b0], D[b1]);
                if (u < INF && v < INF) ans[i] = min(ans[i], (ll)u + v);
            }
        }
    }
    vector<int> L, R;
    for (int i : qs) {
        int lo = min(sy[i], ey[i]), hi = max(sy[i], ey[i]);
        if (hi < mid) L.push_back(i);
        else if (lo > mid) R.push_back(i);
    }
    go(l, mid - 1, L);
    go(mid + 1, r, R);
}

vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end, vector<int>& K) {
    n = N;
    g = &G;
    sx.resize(Q); sy.resize(Q); ex.resize(Q); ey.resize(Q);
    ans.assign(Q, 4e18);
    vector<int> all(Q);
    for (int i = 0; i < Q; i++) {
        sx[i] = start[i].first, sy[i] = start[i].second;
        ex[i] = end[i].first, ey[i] = end[i].second;
        all[i] = i;
    }
    go(0, M - 1, all);
    vector<string> res(Q);
    for (int i = 0; i < Q; i++) res[i] = ans[i] <= K[i] ? "YES" : "NO";
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> G(N);
        for (auto &s : G) cin >> s;
        vector<pair<int, int>> start, end;
        vector<int> K;
        while (Q--) {
            int a, b, c, d, k;
            cin >> a >> b >> c >> d >> k;
            start.push_back({a, b});
            end.push_back({c, d});
            K.push_back(k);
        }
        for (string s : solve(N, M, (int)K.size(), G, start, end, K)) cout << s << '\n';
    }
}
