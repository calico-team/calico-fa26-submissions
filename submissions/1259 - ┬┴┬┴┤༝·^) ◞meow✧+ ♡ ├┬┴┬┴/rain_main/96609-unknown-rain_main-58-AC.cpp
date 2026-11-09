#include <bits/stdc++.h>

using namespace std;

#define int long long

namespace kactl {

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct FT {
  vector<ll> s;
  FT(int n) : s(n) {}
  void update(int pos, ll dif) {  // a[pos] += dif
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) {  // sum of values in [0, pos)
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
  int lower_bound(ll sum) {  // min pos st sum of [0, pos] >= sum
    // Returns n if no sum is >= sum, or -1 if empty sum is.
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = 1 << 25; pw; pw >>= 1) {
      if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    }
    return pos;
  }
};

}  // namespace kactl

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> drones(n, vector<int>(4));
    for (int i = 0; i < n; ++i) {
      int x, y, z;
      char d;
      cin >> x >> y >> z >> d;
      drones[i] = {x, y, z, d == 'N' ? 1 : 0};
    }

    map<int, set<int>> diagonals;
    for (int i = 0; i < n; ++i) {
      if (drones[i][3]) {
        diagonals[drones[i][0] + drones[i][1]].insert(
            floor((drones[i][0] - drones[i][1]) / 2.0));
      }
    }
    int overlaps = 0;
    for (int i = 0; i < n; ++i) {
      if (!drones[i][3]) {
        int diag = drones[i][0] + drones[i][1];
        int startpos = floor((drones[i][0] - drones[i][1]) / 2.0);
        int endpos = startpos + k;
        if (diagonals.count(diag)) {
          auto it = diagonals[diag].lower_bound(startpos);
          auto it2 = diagonals[diag].lower_bound(endpos);
          overlaps += distance(it, it2);
        }
      }
    }
    cout << n * k - overlaps << endl;
  }
}