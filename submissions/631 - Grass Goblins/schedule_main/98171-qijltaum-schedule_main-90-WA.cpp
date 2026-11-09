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
    int N, M, K; cin >> N >> M >> K;

    vec<int> P(N);
    for(auto &x: P) cin >> x;

    vec<vec<int>> adj(N + 1);
    for(int i = 1; i <= N; ++i) {
        adj[P[i - 1]].emplace_back(i);
    }

    int x = 0;

    vec<int> p = {0};
    priority_queue<pii> q;
    for(int d = 0; d <= M; ++d) {
        while(!p.empty()) {
            int u = p.back();
            p.pop_back();

            q.emplace(adj[u].size(), u);
        }

        int sz = 0;
        while(!q.empty() && sz < K) {
            auto [l, u] = q.top();
            q.pop();

            sz += 1;
            x += 1;

            for(auto v: adj[u]) {
                p.emplace_back(v);
            }
        }
    }

    cout << x - 1 << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}
