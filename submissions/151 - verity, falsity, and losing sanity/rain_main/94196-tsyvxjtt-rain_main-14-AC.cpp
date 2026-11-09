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
        int n, k;
        std::cin >> n >> k;

        std::vector<std::array<int, 3>> a(n);
        for(int i = 0; i < n; ++i) {
            int x, y, z; char d;
            std::cin >> x >> y >> z >> d;

            a[i] = {x+y, x, d == 'E'};
        }

        std::sort(a.begin(), a.end());

        long long ans = (long long)n*k;
        std::queue<std::array<int, 2>> q;
        for(auto [s, x, d] : a) {
            while(!q.empty() && (q.front()[0] != s || x-q.front()[1] >= k)) q.pop();

            if(d) q.push({s, x});
            else ans -= (int)q.size();
        }

        std::cout << ans << "\n";
    }

    return 0;
}