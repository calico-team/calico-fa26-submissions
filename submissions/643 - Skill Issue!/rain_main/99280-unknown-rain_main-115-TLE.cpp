/*

Author: Ishaq
 
********************* بسم الله الرحمن الرحيم ***********************
                     
                  ╔════════════════════════╗
                  ║     Muhammad-Ishaq     ║
                  ╚════════════════════════╝
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ull = unsigned long long;
using i128 = __int128_t;

#define int long long
#define CODE_BY_ISHAQ ios::sync_with_stdio(false); cin.tie(nullptr);
#define pb push_back
#define sz(x) ((int) x.size())

constexpr long long LINF = 1e18;
constexpr int INF = 1e9;
const int MAXN = 2e5 + 5;
const long long MOD = 998244353;

template <typename T>
using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;
 
template <typename T>
using ordered_multiset = tree <pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, tree_order_statistics_node_update>;

struct drone {
    int x, y, z;
    char d;
};

void ishaq() {
    int n, k;
    cin >> n >> k;
    vector<drone> v(n);
    map<int, vector<int>> E_y, E_x, N_y, N_x;
    for (int i = 0; i < n; i++) {
        cin >> v[i].x >> v[i].y >> v[i].z >> v[i].d;
        if (v[i].d == 'E') {
            E_x[v[i].x + v[i].y].pb(v[i].x);
            E_y[v[i].x + v[i].y].pb(v[i].y);
        } else {
            N_x[v[i].x + v[i].y].pb(v[i].x);
            N_y[v[i].x + v[i].y].pb(v[i].y);
        }
    }
    for (auto &[x, y] : E_x) {
        sort(y.begin(), y.end());
    }
    for (auto &[x, y] : E_y) {
        sort(y.begin(), y.end());
    }
    for (auto &[x, y] : N_x) {
        sort(y.begin(), y.end());
    }
    for (auto &[x, y] : N_y) {
        sort(y.begin(), y.end());
    }
    k--;
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (v[i].d == 'E') {
            int lbi = lower_bound(N_x[v[i].x + v[i].y].begin(), N_x[v[i].x + v[i].y].end(), v[i].x) - N_x[v[i].x + v[i].y].begin();
            if (lbi >= sz(N_x[v[i].x + v[i].y])) {
                continue;
            }
            int lo = 0, hi = sz(N_x[v[i].x + v[i].y]), idx = -1;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                if (v[i].x + k >= N_x[v[i].x + v[i].y][mid]) {
                    idx = mid;
                    lo = mid + 1;
                } else {
                    hi = mid;
                }
            }
            if (idx == -1) {
                continue;
            }
            c += idx - lbi + 1;
        } else {
            int lbi = lower_bound(E_y[v[i].x + v[i].y].begin(), E_y[v[i].x + v[i].y].end(), v[i].y) - E_y[v[i].x + v[i].y].begin();
            if (lbi >= sz(E_y[v[i].x + v[i].y])) {
                continue;
            }
            int lo = 0, hi = sz(E_y[v[i].x + v[i].y]), idx = -1;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                if (v[i].y + k >= E_y[v[i].x + v[i].y][mid]) {
                    idx = mid;
                    lo = mid + 1;
                } else {
                    hi = mid;
                }
            }
            if (idx == -1) {
                continue;
            }
            c += idx - lbi + 1;
        }
    }
    cout << n * (k + 1) - c / 2 << '\n';
}

signed main() {
  CODE_BY_ISHAQ
  int T = 1;
  cin >> T;
  cout << fixed << setprecision(10);
  while (T--) ishaq();
}