#include <bits/stdc++.h>
#define int long long
using namespace std;
int BIG = 200000;

signed main() {
  string T; cin>>T;
  if (T == "FIRST") {
    int n; cin>>n;
    vector<vector<int>> e(n);
    for (int i = 0; i < n-1; i++) {
      int u, v; cin>>u>>v; u--; v--;
      e[u].push_back(v);
      e[v].push_back(u);
    }
    stack<int> s;
    vector<bool> d(n, false);
    vector<bool> l(n, false);
    vector<int> f;
    d[0] = true;
    s.push(0);
    int x = 0;
    while (!s.empty()) {
      int v = s.top(); s.pop();
      int t = 0;
      for (int i: e[v]) {
        if (!d[i]) {
          d[i] = 1; s.push(i);
          if (t == 0) {
            f.push_back(BIG + i);
            x ^= 1;
          } else {
            f.push_back(i);
          }
          t++;
        }
      }
      if (t == 0) {
        l[v] = true;
      }
    }
    for (int i = 0; i < n-1; i++) {
      if (l[f[i]%BIG]) {
        f[i] += 2*BIG;
        x ^= 2;
      }
    }
    for (int i: f) cout << i + 1 << ' ';
    cout << x+1 << '\n';
  } else {
    int n; cin>>n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin>>a[i];
    for (int i = 0; i < n; i++) a[i]--;
    int x = 0;
    int k = -1;
    int w = 0;
    for (int i = 0; i < n-1; i++) {
      if (a[i] == -2) {
        k = i;
      } else {
        int v = a[i]%BIG;
        w += v;
        x ^= (a[i]-v)/BIG;
      }
    }
    if (k != -1) {
      x ^= a[n-1];
      a[k] = (n)*(n-1)/2-w+x*BIG;
    }
    stack<int> s;
    s.push(0);
    int c = 0;
    for (int i = 0; i < n-1; i++) {
      int v = a[i]%BIG;
      int m = (a[i]-v)/BIG;
      if (m & 1) {
        c = s.top(); s.pop();
      }
      if (!(m & 2)) {
        s.push(v);
      }
      cout << c+1 << ' ' << v+1 << '\n';
    }
  }
}
