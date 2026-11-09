#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

const int MAXN = 200005;
const long long MOD = 998244353;
const long long INF = 1000000000000000000;

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    std::string s; int n;
    std::cin >> s >> n;

    std::vector<long long> a(n+1);
    if(s == "FIRST") {
        std::vector<std::vector<int>> adj(n+1);
        for(int i = 1; i < n; ++i) {
            int u, v;
            std::cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        std::vector<int> q = {1};
        for(int i = 0; i < n; ++i) {
            int u = q[i];
            for(int v : adj[u]) {
                if(v == a[u]) continue;
                a[v] = u;
                q.push_back(v);
            }
        }

        for(int i = 2; i <= n; ++i) a[1] += a[i];
        for(int i = 1; i <= n; ++i) std::cout << a[i] << (i == n ? "\n" : " ");
    } else {
        int pos = 0;
        long long cur = 0;
        for(int i = 1; i <= n; ++i) {
            std::cin >> a[i];
            if(a[i] == -1) pos = i;
            else if(i > 1) cur += a[i];
        }

        a[pos] = (pos == 1 ? cur : a[1]-cur);
        for(int i = 2; i <= n; ++i) std::cout << i << " " << a[i] << "\n";
    }


    return 0;
}