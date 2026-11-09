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
   int n, r; cin >> n >> r;
   vi a(n);
   FOR (i, 0, n) cin >> a[i];

   array<int,2> av = {0, 0};
   FOR (i, 0, n) {
       if (av[0] > av[1]) swap(av[0], av[1]);

       if (av[0] <= a[i]) {
           av[0] = max(a[i], av[1]) + r;
       } else {
           cout << "NO" << '\n';
           return;
       }
   }

   cout << "YES" << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        solve();
    }
}


