#include <bits/stdc++.h>
using namespace std;

int main() {
  int T; cin>>T; while (T--) {
    int n, r; cin>>n>>r;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin>>a[i];
    queue<int> q;
    bool f = true;
    for (int i = 0; i < n; i++) {
      while (!q.empty() && q.front() <= a[i]) {
        q.pop();
      }
      if (q.size() == 2) {
        f = false; break;
      } else if (q.size() == 1) {
        q.push(q.front() + r);
      } else {
        q.push(a[i] + r);
      }
        
    }
    cout << (f ? "YES\n" : "NO\n");
  }
}

