/**
 * @author n685
 * @date Sun 08 Nov 2026 07:04:36 PM EST
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

void tc() {
    int n, r;
    std::cin >> n >> r;

    std::vector<int> a(n);
    for (int& v : a)
        std::cin >> v;

    std::array<int, 2> ch{};
    for (int t : a) {
        if (t >= ch[0]) {
            ch[0] = t + r;
        } else if (t >= ch[1]) {
            ch[1] = ch[0] + r;
        } else {
            std::cout << "NO\n";
            return;
        }
    }
    std::cout << "YES\n";
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
