#include <bits/stdc++.h>
using namespace std;

#include <cassert>

#define lf "\n"
#define ff endl
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#ifdef DEBUG

constexpr bool IS_DEBUG = 1;

#define infor(fmt, ...) do { print(stderr, fmt, ##__VA_ARGS__); } while(0)
#define infof(fmt, ...) do { println(stderr, fmt, ##__VA_ARGS__); } while(0)

#else

constexpr bool IS_DEBUG = 0;

#define infor(fmt, ...)
#define infof(fmt, ...)

#endif /* DEBUG */

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

void solve(void) {
    infof("=======");

    int N, M, K; cin >> N >> M >> K;

    vec<int> P(N + 1);
    for(int i = 1; i <= N; ++i) {
        cin >> P[i];
    }

    vec<vec<int>> adj(N + 1);
    for(int i = 1; i <= N; ++i) {
        adj[P[i]].emplace_back(i);
    }

    int x = 0;

    vec<vec<int>> L(M);
    auto dfs = [&](int u, int d, auto &&dfs) -> void {
        if(d >= M) return;
        L[d].emplace_back(u);

        for(auto v: adj[u]) {
            dfs(v, d + 1, dfs);
        }
    };

    for(auto v: adj[0]) {
        dfs(v, 0, dfs);
    }

    int l = M - 1;
    vec<bool> vis(N + 1);
    vec<int> rm(M, K);

    auto kill = [&](int n) -> void {
        infof("---- kill({}) [l = {}] ----", n, l);
        for(int d = l; n > 0; n = P[n], d--) {
            infof("... vis {} [d = {}]", n, d);
            if(vis[n]) break;
            vis[n] = 1;
            rm[d] -= 1;
        }
    };

    for(int d = M - 1; d >= 0; d--) {
        infof("d = {} | L = {}", d, L[d]);
        for(auto n: L[d]) {
            while(l >= 0 && rm[l] == 0) l -= 1;
            if(l < d) break;
            if(vis[n]) continue;

            kill(n);
        }
    }

    cout << (M * K - accumulate(all(rm), 0)) << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}
