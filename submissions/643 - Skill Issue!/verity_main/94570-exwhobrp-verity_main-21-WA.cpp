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

void ishaq() {
    int n, k;
    cin >> n >> k;
    vector<char> a(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    vector<char> ans(n, '0');
    for (char c : a) {
        for (int i = 0; i < n; i++) {
            if (ans[i] == '0') {
                cout << c << ' ';
            } else {
                cout << ans[i] << ' ';
            }
        }
        cout << endl;
        string s;
        cin >> s;
        if (s == "CORRECT") {
            return;
        }
        for (int i = 0; i < n; i++) {
            if (ans[i] == '0' && s[i] != '_') {
                ans[i] = c;
            }
        }
    }
}

signed main() {
  CODE_BY_ISHAQ
  int T = 1;
  cin >> T;
  cout << fixed << setprecision(10);
  while (T--) ishaq();
}