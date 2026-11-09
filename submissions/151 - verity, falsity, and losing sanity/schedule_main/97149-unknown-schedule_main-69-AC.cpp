#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

const int MAXN = 200005;
const long long MOD = 998244353;
const long long INF = 1000000000000000000;

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int t;
    std::cin >> t;

    while(t--) {
        int n, m, k;
        std::cin >> n >> m >> k;

        std::vector<int> par(n+1), depth(n+1), cnt(m+1);
        for(int i = 1; i <= n; ++i) std::cin >> par[i];

        auto solve = [&](auto &&solve, int u) -> int {
            if(depth[u]) return depth[u];
            if(!par[u]) return depth[u] = 1;

            return depth[u] = solve(solve, par[u])+1;
        };

        for(int i = 1; i <= n; ++i) {
            int x = solve(solve, i);
            if(x <= m) ++cnt[x];
        }

        int ans = m*k, cur = 0;
        for(int i = 1; i <= m; ++i) {
            cur += cnt[i];
            ans = std::min(ans, cur+(m-i)*k);
        }

        std::cout << ans << "\n";
    }

    return 0;
}