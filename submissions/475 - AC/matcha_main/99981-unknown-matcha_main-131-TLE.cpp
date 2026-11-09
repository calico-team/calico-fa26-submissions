#include <bits/stdc++.h>
using namespace std;

using interval = pair<int, int>;
interval operator * (const interval& a, const interval& b) {
  int d = max(a.second-a.first, b.second-b.first);
  int lo = (a.first^b.first) & ~(d-1);
  return make_pair(lo, lo+d);
}

vector<interval> decompose(int l, int r) {
  r += 1;
  vector<interval> res;
  while (l < r) {
    int m = l&-l;
    if (m > 0 && l+m <= r) {
      res.emplace_back(l, l+m);
      l += m;
      continue;
    }
    int b = __lg(r-l);
    m = 1<<b;
    res.emplace_back(l, l+m);
    l += m;
  }
  return res;
}

bool check(int l, int r) {
  int d = r-l;
  if (d&(d-1)) return 0;
  if (l&(d-1)) return 0;
  return 1;
}

int main () {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> l(n), r(n);
    for (auto& x: l) cin >> x;
    for (auto& x: r) cin >> x;
    vector<interval> dp;
    dp.emplace_back(0, 1);
    for (int i = 0; i < n; i++) {
      vector<interval> ndp;
      vector<interval> parts = decompose(l[i], r[i]);
      for (auto& x: dp) {
        for (auto& y: parts) {
          ndp.emplace_back(x*y);
        }
      }
      swap(ndp, dp);
      sort(dp.begin(), dp.end());
      int sz = 0;
      for (int i = 0; i < (int)dp.size(); i++) {
        auto [l1, r1] = dp[i];
        while (1) {
          if (sz == 0) {
            dp[sz++] = dp[i];
            break;
          }
          auto [l2, r2] = dp[sz-1];
          if (l2 >= l1) {
            sz--;
            continue;
          }
          if (l2 <= l1 && r1 <= r2) break;
          if (l1 <= l2 && r2 <= r1) {
            dp[sz-1] = dp[i];
            break;
          }
          if (r2 < l1) {
            dp[sz++] = dp[i];
            break;
          }
          if (check(l2, r1)) {
            dp[sz-1] = make_pair(l2, r1);
            break;
          }
          else {
            dp[sz++] = dp[i];
            break;
          }
        }
      }

      dp.resize(sz);
    }
    cout << dp.back().second-1 << '\n';
  }
}
