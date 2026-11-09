#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    static uint64_t tr[256][256][2][4];
    for (int k = 0; k < 256; k++) {
        for (int s = 0; s < 256; s++) {
            for (int v = 0; v < 16; v++) {
                int ns = 0;
                bool ok = true;
                for (int i = 0; i < 4; i++) {
                    int j = 2 * (3 - i);
                    int p = (s >> j) & 3;
                    int a = (v >> i) & 1;
                    int lo = (k >> (2 * i + 1)) & 1;
                    int hi = (k >> (2 * i)) & 1;
                    if (((p & 1) && a < lo) ||
                        ((p & 2) && a > hi)) {
                        ok = false;
                        break;
                    }
                    int pp = ((p & 1) && a == lo) |
                             (((p & 2) && a == hi) << 1);
                    ns |= pp << j;
                }
                if (ok) {
                    int h = __builtin_parity((unsigned)v);
                    tr[k][s][h][ns >> 6] |= 1ULL << (ns & 63);
                }
            }
        }
    }
    using P = pair<int, int>;
    const int mk = (1 << 30) - 1;
    auto pk = [](int a, int b) -> uint64_t {
        return (uint64_t)(unsigned)b << 30 | (unsigned)a;
    };
    auto nor = [&](vector<P> v) -> vector<P> {
        unordered_set<uint64_t> st;
        st.reserve(v.size() * 3 + 30);
        vector<uint64_t> q;
        for (auto [a, b] : v) {
            uint64_t z = pk(a, b);
            if (st.insert(z).second) {
                q.push_back(z);
            }
        }
        for (size_t i = 0; i < q.size(); i++) {
            uint64_t z = q[i];

            if (!st.count(z)) {
                continue;
            }
            int a = z & mk;
            int b = z >> 30;
            for (int j = 0; j < 30; j++) {
                int t = 1 << j;
                if (!(a & t) && !(b & t)) {
                    uint64_t y = pk(a ^ t, b);
                    if (st.erase(y)) {
                        st.erase(z);
                        uint64_t w = pk(a, b | t);
                        if (st.insert(w).second) {
                            q.push_back(w);
                        }
                        break;
                    }
                }
            }
        }
        v.clear();
        for (uint64_t z : st) {
            v.push_back({
                (int)(z & mk),
                (int)(z >> 30)
            });
        }
        sort(v.begin(), v.end(), [](P a, P b) {
            return __builtin_popcount((unsigned)a.second) >
                   __builtin_popcount((unsigned)b.second);
        });
        vector<P> w;
        for (auto [a, b] : v) {
            bool ok = true;
            for (auto [c, d] : w) {
                if ((b & ~d) == 0 &&
                    ((a ^ c) & ~d) == 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                w.push_back({a, b});
            }
        }
        return w;
    };
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> l(max(n, 4), 0);
        vector<int> r(max(n, 4), 0);
        for (int i = 0; i < n; i++) {
            cin >> l[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> r[i];
        }
        if (n == 1) {
            cout << r[0] << '\n';
            continue;
        }
        if (n <= 4) {
            uint64_t u[4] = {0, 0, 0, 1ULL << 63};
            int ans = 0;
            for (int j = 29; j >= 0; j--) {
                int k = 0;
                for (int i = 0; i < 4; i++) {
                    k |= ((l[i] >> j) & 1) << (2 * i + 1);
                    k |= ((r[i] >> j) & 1) << (2 * i);
                }
                uint64_t v[2][4] = {};
                for (int i = 0; i < 4; i++) {
                    for (uint64_t t = u[i]; t; t &= t - 1) {
                        int s = i * 64 + __builtin_ctzll(t);
                        for (int h = 0; h < 4; h++) {
                            v[0][h] |= tr[k][s][0][h];
                            v[1][h] |= tr[k][s][1][h];
                        }
                    }
                }
                if (v[1][0] | v[1][1] |
                    v[1][2] | v[1][3]) {
                    ans |= 1 << j;
                    memcpy(u, v[1], sizeof u);
                } else {
                    memcpy(u, v[0], sizeof u);
                }
            }
            cout << ans << '\n';
            continue;
        }
        int xo = 0;
        int fm = 0;
        vector<vector<P>> all;
        for (int i = 0; i < n; i++) {
            int a = l[i];
            int b = r[i];
            if (b - a <= 1) {
                xo ^= a ^ (a >> 1);
                if (b > a) {
                    fm |= (a ^ (a >> 1)) ^
                          (b ^ (b >> 1));
                }
                continue;
            }
            vector<P> v;
            for (int u = a; u <= b;) {
                int k = u ? __builtin_ctz((unsigned)u) : 30;
                while ((1LL << k) > b - u + 1LL) {
                    k--;
                }
                int m = (1 << k) - 1;
                int z = (u ^ (u >> 1)) & ~m;
                v.push_back({z, m});
                u += 1 << k;
            }
            if (v.size() == 1) {
                xo ^= v[0].first;
                fm |= v[0].second;
            } else {
                all.push_back(move(v));
            }
        }
        sort(all.begin(), all.end(),
             [](const vector<P>& a, const vector<P>& b) {
                 return a.size() > b.size();
             });
        vector<P> s = {{0, fm}};
        for (auto &v : all) {
            vector<P> w;
            w.reserve(s.size() * v.size());
            for (auto [a, b] : s) {
                for (auto [c, d] : v) {
                    int m = b | d;
                    w.push_back({(a ^ c) & ~m, m});
                }
            }
            s = nor(move(w));
        }
        int ans = 0;
        for (auto [a, b] : s) {
            a = (a ^ xo) & ~b;
            int z = 0;
            int p = 0;
            for (int j = 29; j >= 0; j--) {
                int g;
                if ((b >> j) & 1) {
                    g = p ^ 1;
                } else {
                    g = (a >> j) & 1;
                }
                p ^= g;
                z |= p << j;
            }
            ans = max(ans, z);
        }
        cout << ans << '\n';
    }
    return 0;
}