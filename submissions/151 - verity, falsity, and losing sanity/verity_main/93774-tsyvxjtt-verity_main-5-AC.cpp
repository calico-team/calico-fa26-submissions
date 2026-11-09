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

        std::vector<char> a(k);
        for(int i = 0; i < k; ++i) std::cin >> a[i];

        std::string s;
        for(int i = 0; i < n; ++i) s += '_';
        
        for(int i = 0; i < k; ++i) {
            for(int j = 0; j < n; ++j) {
                if(s[j] == '_') s[j] = a[i];
            }

            std::cout << s << "\n" << std::flush;

            std::cin >> s;
            if(s == "CORRECT") break;
        }
    }

    return 0;
}