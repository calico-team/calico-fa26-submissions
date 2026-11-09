#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
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
            int a = z & mk, b = z >> 30;
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
            v.push_back({(int)(z & mk), (int)(z >> 30)});
        }
        sort(v.begin(), v.end(), [](P a, P b) {
            return __builtin_popcount((unsigned)a.second) >
                   __builtin_popcount((unsigned)b.second);
        });
        vector<P> w;
        for (auto [a, b] : v) {
            bool ok = true;
            for (auto [c, d] : w) {
                if ((b & ~d) == 0 && ((a ^ c) & ~d) == 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) w.push_back({a, b});
        }
        return w;
    };
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> l(n), r(n);
        for (int &x : l) {
            cin >> x;
        }
        for (int &x : r) {
            cin >> x;
        }
        vector<unsigned> edges(n);
        unsigned allBits = 0, seenBits = 0;
        int matching[30];
        fill(matching, matching + 30, -1);
        int matched = 0;
        function<bool(int)> augment = [&](int i) -> bool {
            unsigned available = edges[i] & ~seenBits;
            while (available) {
                int b = __builtin_ctz(available);
                available &= available - 1;
                seenBits |= 1u << b;
                if (matching[b] == -1 || augment(matching[b])) {
                    matching[b] = i;
                    return true;
                }
            }
            return false;
        };
        unsigned base = 0;
        for (int i = 0; i < n; ++i) {
            base ^= unsigned(l[i]) ^ (unsigned(l[i]) >> 1);
            unsigned bits = 0;
            for (int b = 0; b < 30; ++b) {
                unsigned first = (unsigned(l[i]) >> b) + 1;
                if (!(first & 1u)) ++first;
                if (first <= (unsigned(r[i]) >> b)) bits |= 1u << b;
            }
            edges[i] = bits;
            allBits |= bits;
            if (matched < __builtin_popcount(allBits)) {
                seenBits = 0;
                if (augment(i)) ++matched;
            }
        }
        if (matched == __builtin_popcount(allBits)) {
            unsigned result = 0, prefix = 0;
            for (int b = 29; b >= 0; --b) {
                unsigned gray = (allBits >> b & 1u)
                    ? (prefix ^ 1u) : (base >> b & 1u);
                prefix ^= gray;
                result |= prefix << b;
            }
            cout << result << '\n';
            continue;
        }
        int xo = 0, fm = 0;
        vector<vector<P>> all;
        for (int i = 0; i < n; i++) {
            int a = l[i];
            int b = r[i];
            if (b - a <= 1) {
                xo ^= a ^ (a >> 1);
                if (b > a) fm |= (a ^ (a >> 1)) ^ (b ^ (b >> 1));
                continue;
            }
            vector<P> v;
            for (int u = a; u <= b;) {
                int k = u ? __builtin_ctz((unsigned)u) : 30;
                while ((1LL << k) > b - u + 1LL) {
                    k--;
                }
                int m = (1 << k) - 1, z = (u ^ (u >> 1)) & ~m;
                v.push_back({z, m});
                u += (1 << k);
            }
            v = nor(move(v));
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
            int z = 0, p = 0;
            for (int j = 29; j >= 0; j--) {
                int g;
                if ((b >> j) & 1) g = p ^ 1;
                else g = (a >> j) & 1;
                p ^= g;
                z |= p << j;
            }
            ans = max(ans, z);
        }
        cout << ans << '\n';
    }
    return 0;
}