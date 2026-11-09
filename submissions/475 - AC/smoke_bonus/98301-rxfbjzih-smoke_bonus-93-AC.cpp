#include <bits/stdc++.h>
using namespace std;

int main () {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, r;
    cin >> n >> r;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    int t1 = 0, t2 = r;
    bool ok = 1;
    for (int i = 1; i < n; i++) {
      int d = a[i]-a[i-1];
      int c = min(d, t1);
      d -= c;
      t1 -= c;
      c = min(d, t2);
      d -= c;
      t2 -= c;
      if (t1 > 0) {
        ok = 0;
        break;
      }
      tie(t1, t2) = make_pair(t2, r);
    }
    cout << (ok ? "YES" : "NO") << '\n';
  }
}
