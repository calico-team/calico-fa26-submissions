#include <bits/stdc++.h>
using namespace std;

int main () {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    int y = 0;
    vector<int> l(n), r(n);
    for (auto& x: l) cin >> x;
    for (auto& x: r) cin >> x;
    vector<int> vals;
    for (int i = 0; i < n; i++) {
      y ^= l[i];
      if (l[i] < r[i]) {
        int b = __lg(l[i]^r[i]);
        int rx = r[i] & ~((1<<b)-1);
        int lx = rx-1;
        vals.emplace_back(lx^rx);
        for (int e = 0; e < 30; e++) {
          if (rx+(1<<e) <= r[i] || lx-(1<<e) >= l[i]) vals.emplace_back(1<<e);
        }
      }
    }
    vector<int> basis;
    for (int x: vals) {
      for (int j = 0; j < (int)basis.size(); j++) {
        if ((x ^ basis[j]) < x) x ^= basis[j];
      }
      if (x > 0) {
        [&] () {
          for (int j = 0; j < (int)basis.size(); j++) {
            if (x > basis[j]) {
              basis.insert(basis.begin() + j, x);
              return;
            }
          }
          basis.emplace_back(x);
        } ();
      }
    }
    for (int x: basis) y = max(y, y^x);
    cout << y << '\n';
  }
}
