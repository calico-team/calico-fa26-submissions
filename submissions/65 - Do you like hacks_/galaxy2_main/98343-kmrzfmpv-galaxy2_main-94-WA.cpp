/**
 * @author n685
 * @date Sun 08 Nov 2026 07:39:27 PM EST
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

#ifndef TEMPL_DSU_H
#define TEMPL_DSU_H


struct DSU {
    std::vector<int> vals;
    int cnt{};
    DSU() = default;
    explicit DSU(int n) : vals(n, -1), cnt(n) {}
    int find(int i) { return vals[i] < 0 ? i : (vals[i] = find(vals[i])); }
    bool unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v)
            return false;
        // if (vals[u] > vals[v])
        //     std::swap(u, v);
        vals[u] += vals[v];
        vals[v] = u;
        --cnt;
        return true;
    }
    bool connected(int u, int v) { return find(u) == find(v); }
    int size(int u) { return -vals[find(u)]; }
    int count() const { return cnt; }
};

#endif

void tc() {
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<int> r(q), c(q), p(q);
    for (int i = 0; i < q; ++i) {
        std::cin >> r[i] >> c[i] >> p[i];
    }
    bool flip = n > m;
    if (flip) {
        std::swap(n, m);
        std::swap(r, c);
    }

    std::vector ans(n, std::vector<i64>(m));
    std::vector<int> rad(q);
    for (int i = 0; i < n; ++i) {
        DSU dsu(m + 1);
        for (int j = q - 1; j >= 0; --j) {
            i64 dx = (i64)(i - r[j]) * (i - r[j]);
            if ((i64)p[j] * p[j] - dx + 1 <= 0)
                continue;
            // p[j]^2 - (i - r[j])^2 + 1 - rad^2 > 0
            // rad^2 < p[j]^2 - (i - r[j])^2 + 1
            if (i <= r[j]) {
                while ((i64)rad[j] * rad[j] < (i64)p[j] * p[j] - dx + 1)
                    ++rad[j];
                --rad[j];
            } else {
                while ((i64)rad[j] * rad[j] >= (i64)p[j] * p[j] - dx + 1)
                    --rad[j];
            }
            int lf = c[j] - rad[j];
            while (true) {
                int cur = dsu.find(lf);
                dbg(lf, cur, m);
                if (cur <= c[j] + rad[j]) {
                    ans[i][cur] = (i64)p[j] * p[j] - dx - (i64)(cur - c[j]) * (cur - c[j]) + 1;
                    dsu.unite(cur + 1, cur);
                } else {
                    break;
                }
            }
        }
    }

    if (flip) {
        std::vector a(m, std::vector<i64>(n));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = ans[j][i];
        std::swap(n, m);
        a.swap(ans);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            std::cout << ans[i][j] << ' ';
        std::cout << '\n';
    }
}

int main() {
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif

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
