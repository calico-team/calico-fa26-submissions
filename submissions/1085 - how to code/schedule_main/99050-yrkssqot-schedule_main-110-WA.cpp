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
    vi p(n);
    FOR (i, 0, n) {
        cin >> p[i];
        p[i]--;
    }

    vi nm(n);
    vb v(n);

    auto dfs = [&] (auto&& self, int u) -> void {
        v[u] = true;
        if (p[u] == -1) nm[u] = 0;
        else if (v[p[u]]) nm[u] = nm[p[u]] + 1;
        else {
            self(self, p[u]);
            nm[u] = nm[p[u]] + 1;
        }
    };

    for (int i = 0; i < n; i++) {
        if (!v[i]) dfs(dfs, i);
    }

    sort(all(nm));


    int p1 = 0, cr = 0, p2 = 0;

    while (p1 < m and p2 < n) {
        while (p2 < n and cr < k) {
            if (p2 != 0 and cr != 0 and nm[p2] != nm[p2 - 1]) break;
            cr++, p2++;
        }
        p1++;
        cr = 0;
    }

    cout << p2 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        solve();
    }
}


