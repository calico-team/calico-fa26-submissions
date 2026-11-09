#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Row {
    vector<ull> b;
    int rhs, piv, cnt;
};

int m, W, stamp, cnt01, nr, nt;
ll B;
vector<ull> col[30], tb, vb;
Row rows[32];
int touched[32];
vector<int> ys, inY, want, mark, val;

int bit(const vector<ull>& v, int i) {
    return v[i >> 6] >> (i & 63) & 1;
}

int ones(const vector<ull>& v) {
    int c = 0;
    for (ull x : v) c += __builtin_popcountll(x);
    return c;
}

bool isZero(const vector<ull>& v) {
    for (ull x : v) if (x) return false;
    return true;
}

void xorInto(vector<ull>& a, const vector<ull>& b) {
    for (int i = 0; i < W; i++) a[i] ^= b[i];
}

bool ok(int mode) {
    stamp++;
    int bad = 0;
    for (int i = 0; i < nr; i++) {
        Row& r = rows[i];
        if (r.cnt != 1) continue;
        mark[r.piv] = stamp;
        val[r.piv] = r.rhs;
        if (inY[r.piv] && r.rhs != want[r.piv]) bad++;
    }
    int good = ys.size() - bad;
    if (mode == 1) return cnt01 > 0 || good > 0;
    if (cnt01 >= 2) return true;
    if (cnt01 == 1) return good > 0;
    if (good != 2) return good > 2;

    int y = -1, z = -1;
    for (int i : ys) {
        if (mark[i] == stamp && val[i] != want[i]) continue;
        if (y < 0) y = i;
        else { z = i; break; }
    }
    if (mark[y] == stamp || mark[z] == stamp) return true;

    vector<ull>& v = vb;
    fill(v.begin(), v.end(), 0);
    v[y >> 6] ^= 1ULL << (y & 63);
    v[z >> 6] ^= 1ULL << (z & 63);
    int c = 0;
    for (int i = 0; i < nr; i++) {
        Row& r = rows[i];
        if (r.piv == y || r.piv == z) {
            xorInto(v, r.b);
            c ^= r.rhs;
        }
    }
    if (!isZero(v)) return true;
    return c == (want[y] ^ want[z]);
}

int reduce(vector<ull>& t) {
    int r = 0;
    for (int i = 0; i < nr; i++) {
        Row& row = rows[i];
        if (bit(t, row.piv)) {
            xorInto(t, row.b);
            r ^= row.rhs;
        }
    }
    return r;
}

void add(const vector<ull>& t, int rhs) {
    int p = 0;
    while (!bit(t, p)) p++;
    nt = 0;
    for (int i = 0; i < nr; i++) {
        if (bit(rows[i].b, p)) {
            xorInto(rows[i].b, t);
            rows[i].rhs ^= rhs;
            rows[i].cnt = ones(rows[i].b);
            touched[nt++] = i;
        }
    }
    Row& r = rows[nr++];
    copy(t.begin(), t.end(), r.b.begin());
    r.rhs = rhs, r.piv = p, r.cnt = ones(t);
}

ll solve(int J, int mode, ll cur) {
    nr = 0;
    if (mode == 1) {
        const vector<ull>& t = col[J];
        int r = B >> J & 1;
        if (isZero(t)) {
            if (r) return -1;
        } else {
            add(t, r);
        }
    }
    if (!ok(mode)) return -1;

    ll hi = 0;
    for (int b = 29; b > J; b--) {
        vector<ull>& t = tb;
        copy(col[b].begin(), col[b].end(), t.begin());
        int r = (B >> b & 1) ^ reduce(t);
        if (isZero(t)) {
            if (r) hi |= 1LL << b;
            continue;
        }
        add(t, r ^ 1);
        if (ok(mode)) {
            hi |= 1LL << b;
        } else {
            rows[nr - 1].rhs ^= 1;
            for (int i = 0; i < nt; i++) rows[touched[i]].rhs ^= 1;
        }
        if ((hi | ((1LL << b) - 1)) <= cur) return -1;
    }
    return hi | ((1LL << (J + 1)) - 1);
}

ll rd() {
    int c = getchar_unlocked();
    while (c < '0') c = getchar_unlocked();
    ll x = 0;
    while (c >= '0') x = x * 10 + c - '0', c = getchar_unlocked();
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    T = rd();
    while (T--) {
        int n;
        n = rd();
        vector<ll> L(n), R(n);
        for (auto& x : L) x = rd();
        for (auto& x : R) x = rd();

        B = 0;
        vector<ll> vl, vr, d;
        for (int i = 0; i < n; i++) {
            B ^= L[i];
            if (L[i] != R[i]) {
                vl.push_back(L[i]);
                vr.push_back(R[i]);
                d.push_back(L[i] ^ R[i]);
            }
        }
        m = d.size();

        ll bas[30] = {};
        for (ll x : d) {
            for (int j = 29; j >= 0; j--) {
                if (!(x >> j & 1)) continue;
                if (!bas[j]) { bas[j] = x; break; }
                x ^= bas[j];
            }
        }
        ll ans = B;
        for (int j = 29; j >= 0; j--)
            if (bas[j] && !(ans >> j & 1)) ans ^= bas[j];
        ll best = ans;

        if (m > 0) {
            W = (m + 63) / 64;
            tb.assign(W, 0);
            vb.assign(W, 0);
            for (int i = 0; i < 32; i++) rows[i].b.assign(W, 0);
            for (int j = 0; j < 30; j++) {
                col[j].assign(W, 0);
                for (int i = 0; i < m; i++)
                    if (d[i] >> j & 1) col[j][i >> 6] |= 1ULL << (i & 63);
            }
            vector<int> top(m);
            for (int i = 0; i < m; i++) top[i] = 63 - __builtin_clzll(d[i]);
            inY.assign(m, 0);
            want.assign(m, 0);
            mark.assign(m, 0);
            val.assign(m, 0);
            stamp = 0;

            for (int J = 0; J < 29; J++) {
                if (ans >= (1 << 30) - 1) break;
                ll ub = (best >> (J + 1) << (J + 1)) | ((1LL << (J + 1)) - 1);
                if (ub <= ans) continue;

                ys.clear();
                cnt01 = 0;
                for (int i = 0; i < m; i++) {
                    inY[i] = 0;
                    if (top[i] <= J) continue;
                    int p = vl[i] >> J & 1, q = vr[i] >> J & 1;
                    if (!p && q) cnt01++;
                    else if (p == q) {
                        inY[i] = 1;
                        want[i] = p;
                        ys.push_back(i);
                    }
                }
                if (cnt01 == 0 && ys.empty()) continue;
                ans = max(ans, solve(J, 0, ans));
                ans = max(ans, solve(J, 1, ans));
            }
        }
        cout << ans << '\n';
    }
    return 0;
}