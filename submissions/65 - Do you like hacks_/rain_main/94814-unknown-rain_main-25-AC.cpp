/**
 * @author n685
 * @date Sun 08 Nov 2026 07:16:01 PM EST
 */
#include <bits/stdc++.h>
#include <cassert>

#ifdef LOCAL
#include "dd/debug.h"
#else
#define dbg(...) 67
#define dbg_proj(...) 67
#define dbg_rproj(...) 67
void nline() {}
void bar() {}
void start_clock() {}
void end_clock() {}
#endif

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

#ifndef TEMPL_FENWICK_H
#define TEMPL_FENWICK_H


template <class T> struct Fenwick {
    int len = 0;
    std::vector<T> vals;
    Fenwick() = default;
    explicit Fenwick(int len_) : len(len_), vals(len + 1) {}
    void upd(int i, T val) {
        for (++i; i <= len; i += (i & -i))
            vals[i] += val;
    }
    void set(int i, T val) { upd(i, val - query(i, i)); }
    T sum(int r) const {
        T ans{0};
        for (++r; r > 0; r -= (r & -r))
            ans += vals[r];
        return ans;
    }
    T query(int l, int r) const {
        if (l > r)
            return T{0};
        return sum(r) - sum(l - 1);
    }
#ifdef LOCAL
    std::vector<T> debug() {
        std::vector<T> a;
        for (int i = 0; i < len; ++i) {
            a.push_back(query(i, i));
        }
        return a;
    }
#else
    int debug() { return 67; }
#endif
};

#endif

constexpr int MX = (int)1e5;

struct Point {
    int x, z;
    char d;
};
Fenwick<int> fw;

void tc() {
    int n, k;
    std::cin >> n >> k;

    i64 ans = (i64)n * k;
    std::vector<std::vector<Point>> l(2 * MX + 1);
    for (int i = 0; i < n; ++i) {
        int x, y, z;
        char d;
        std::cin >> x >> y >> z >> d;
        l[x + y].push_back(Point{x, z, d});
    }

    for (int c = 0; c <= 2 * MX; ++c) {
        // std::ranges::sort(l[c], {}, &Point::x);
        std::sort(l[c].begin(), l[c].end(), [&](Point a, Point b) { return a.x < b.x; });
        for (auto [x, z, d] : l[c]) {
            dbg(c, x, z, d);
            if (d == 'E') {
                fw.upd(x, 1);
            } else {
                ans -= fw.query(std::max(0, x - k + 1), x);
            }
        }
        for (auto [x, z, d] : l[c]) {
            if (d == 'E')
                fw.upd(x, -1);
        }
    }
    std::cout << ans << '\n';
}

int main() {
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif

    fw = Fenwick<int>(MX + 1);

    int t;
    std::cin >> t;
    for (int i = 1; i <= t; ++i) {
#ifdef LOCAL
        std::cerr << "Case #" << i << ":\n";
#endif
        tc();
        bar();
    }
}
