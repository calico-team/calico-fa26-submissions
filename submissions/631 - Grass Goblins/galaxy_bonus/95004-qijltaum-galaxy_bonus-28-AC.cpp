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

constexpr int INF = 1e9;

void solve(void) {
    int N, M, Q; cin >> N >> M >> Q;

    vec<string> G(N);
    for(auto &s: G) cin >> s;

    auto is_okay = [&](char A, char B) -> bool {
        return A == '.' || B == '.' || A == B;
    };

    vector col(N, vec<int>(M));
    auto dfs = [&](int x, int y, int c, auto &&dfs) -> void {
        if(col[x][y] > 0) return;
        col[x][y] = c;

        if(x > 0 && is_okay(G[x][y], G[x - 1][y])) {
            dfs(x - 1, y, c, dfs);
        }

        if(x < N - 1 && is_okay(G[x][y], G[x + 1][y])) {
            dfs(x + 1, y, c, dfs);
        }

        if(y > 0 && is_okay(G[x][y], G[x][y - 1])) {
            dfs(x, y - 1, c, dfs);
        }

        if(y < M - 1 && is_okay(G[x][y], G[x][y + 1])) {
            dfs(x, y + 1, c, dfs);
        }
    };

    int c = 1;
    for(int x = 0; x < N; ++x) {
        for(int y = 0; y < M; ++y) {
            if(col[x][y] == 0) {
                dfs(x, y, c++, dfs);
            }
        }
    }

    for(int qi = 0; qi < Q; ++qi) {
        int x1, y1; cin >> x1 >> y1;
        int x2, y2; cin >> x2 >> y2;

        cout << (col[x1][y1] == col[x2][y2] ? "YES" : "NO") << lf;
    }
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}
