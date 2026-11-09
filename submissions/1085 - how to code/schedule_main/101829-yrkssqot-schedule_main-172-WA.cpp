#include <bits/stdc++.h>
using namespace std;
#define int int64_t 

using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vector<int>>;
using ll = long long;
using str = string;
using pi = array<int,2>;

#define sz(x) int(x.size())
#define lb lower_bound
#define ub upper_bound
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define pb push_back

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define rep(a) FOR(_, 0, a)

const int MOD = 998244353;
const int INF = 1e18;

constexpr int pcnt(int x) { return __builtin_popcountll(x);}

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vvi g(n);

    FOR (i, 0, n) {
        int p; cin >> p;
        if (p != 0) g[--p].pb(i);
    }

    set<int> s;
    for (int i = 0; i < m; i++) s.insert(i);
    vi ct(m, k);
    vb v(n);

    int ans = 0;

    auto dfs = [&] (auto&& self, int u, int p, bool f) -> void {
        v[u] = true;
        bool nx = f;
        int tm = p;

        if (f) {
            auto it = s.upper_bound(p);
            if (it == s.end()) nx = false;
            else {
                ans++;
                ct[*it]--;
                tm = *it;
                if (ct[*it] == 0) s.erase(*it);
            }
        }

        for (auto vr : g[u]) {
            self(self, vr, tm, nx);
        }
    };

    for (int i = 0; i < n; i++) {
        if (!v[i]) {
            dfs(dfs, i, -1, true);
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        solve();
    }
}


