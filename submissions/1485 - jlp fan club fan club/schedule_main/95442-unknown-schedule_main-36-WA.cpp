#include <bits/stdc++.h>
using namespace std;

int main() {
  //cin.tie(nullptr); ios_base::sync_with_stdio(false);
  int T; cin>>T; while (T--) {
    int n, m, k; cin>>n>>m>>k;
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin>>p[i];
    for (int i = 0; i < n; i++) p[i]--;
    vector<vector<int>> s(n);
    for (int i = 0; i < n; i++) {
      if (p[i] != -1) {
        s[p[i]].push_back(i);
      }
    }
    queue<int> q;
    queue<int> f;
    int R = 0;
    for (int i = 0; i < n; i++) {
      if (p[i] == -1) q.push(i);
    }
    for (int i = 0; i < m; i++) {
      int w = k;
      while (!q.empty() && w > 0) {
        R++;
        int v = q.front(); q.pop();
        for (int j: s[v]) f.push(j);
        w--;
      }
      while (!f.empty()) {
        int v = f.front(); f.pop();
        q.push(v);
      }
    }
    cout << R << '\n';
  }
}
