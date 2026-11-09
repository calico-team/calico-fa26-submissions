#include <bits/stdc++.h>
using namespace std;
struct Sol {
    int n, m;
    vector<unsigned char> ac;
    vector<array<int, 5>> qs;
    vector<char> ans;
    void dfs(int l, int r, vector<int>& ix) {
        if (ix.empty() || l > r) return;
        int md = (l + r) / 2, sz = (r - l + 1) * n * 2, nn = 2 * n;
        vector<int> ds(nn * sz, -1);
        vector<int> qu(sz);
        for (int a = 0; a < nn; a++) {
            int rw = a / 2, mo = a % 2;
            if (!(ac[md * n + rw] & (1 << mo))) {
                continue;
            }
            int* dp = ds.data() + a * sz;
            int st = ((md - l) * n + rw) * 2 + mo;
            int hd = 0, tl = 0;
            qu[tl++] = st;
            dp[st] = 0;
            while (hd < tl) {
                int v = qu[hd++], z = v >> 1;
                int rr = z % n, cc = z / n, gc = (l + cc) * n + rr;
                int mm = v & 1, dd = dp[v] + 1, nv;
                if (ac[gc] == 3) {
                    nv = v ^ 1;
                    if (dp[nv] == -1) {
                        dp[nv] = dd;
                        qu[tl++] = nv;
                    }
                }
                if (rr > 0 && (ac[gc - 1] & (1 << mm))) {
                    nv = v - 2;
                    if (dp[nv] == -1) {
                        dp[nv] = dd;
                        qu[tl++] = nv;
                    }
                }
                if (rr + 1 < n && (ac[gc + 1] & (1 << mm))) {
                    nv = v + 2;
                    if (dp[nv] == -1) {
                        dp[nv] = dd;
                        qu[tl++] = nv;
                    }
                }
                if (cc > 0 && (ac[gc - n] & (1 << mm))) {
                    nv = v - 2 * n;
                    if (dp[nv] == -1) {
                        dp[nv] = dd;
                        qu[tl++] = nv;
                    }
                }
                if (cc + l < r && (ac[gc + n] & (1 << mm))) {
                    nv = v + 2 * n;
                    if (dp[nv] == -1) {
                        dp[nv] = dd;
                        qu[tl++] = nv;
                    }
                }
            }
        }
        vector<int> lt, rt;
        for (int i : ix) {
            if (ans[i]) continue;
            auto& q = qs[i];
            int sp = ((q[1] - l) * n + q[0]) * 2, tp = ((q[3] - l) * n + q[2]) * 2, tk = ac[q[3] * n + q[2]];
            for (int a = 0; a < nn; a++) {
                int* dp = ds.data() + a * sz;
                int x = dp[sp];
                int y = -1;
                if (tk & 1) y = dp[tp];
                if (tk & 2) {
                    int z = dp[tp + 1];
                    if (z != -1 && (y == -1 || z < y)) {
                        y = z;
                    }
                }
                if (x != -1 && y != -1 && x + y <= q[4]) {
                    ans[i] = 1;
                    break;
                }
            }
            if (!ans[i]) {
                if (q[1] < md && q[3] < md) lt.push_back(i);
                if (q[1] > md && q[3] > md) rt.push_back(i);
            }
        }
        if (!lt.empty()) dfs(l, md - 1, lt);
        if (!rt.empty()) dfs(md + 1, r, rt);
    }
};
int main() {
    int t;
    cin >> t;
    while (t--) {
        Sol so;
        int q;
        cin >> so.n >> so.m >> q;
        so.ac.resize(so.n * so.m);
        for (int i = 0; i < so.n; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < so.m; j++) {
                if (s[j] == '.') so.ac[j * so.n + i] = 3;
                else if (s[j] == 'B') so.ac[j * so.n + i] = 1;
                else so.ac[j * so.n + i] = 2;
            }
        }
        so.qs.resize(q);
        so.ans.assign(q, 0);
        vector<int> ix(q);
        iota(ix.begin(), ix.end(), 0);
        for (auto& a : so.qs) {
            for (int& x : a) {
                cin >> x;
            }
        }
        so.dfs(0, so.m - 1, ix);
        for (char a : so.ans) {
            cout << (a ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}