#include <bits/stdc++.h>
using namespace std;

int main () {
  ios_base::sync_with_stdio(0); cin.tie(0);
  string player;
  cin >> player;
  if (player == "FIRST") {
    int n;
    cin >> n;
    vector<vector<int>> G(n);
    for (int i = 0; i < n-1; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      G[u].push_back(v);
      G[v].push_back(u);
    }
    vector<int> par(n);
    auto dfs = [&] (auto&& self, int v, int p) -> void {
      par[v] = p;
      for (auto& u: G[v]) {
        if (u == p) continue;
        self(self, u, v);
      }
    };
    dfs(dfs, 0, -1);

    int sum = 0;
    for (int i = 1; i < n; i++) sum = (sum + par[i]) % n;
    par[0] = (n-sum)%n;
    for (auto& x: par) cout << x << ' ';
    cout << endl;
  }
  else {
    int n;
    cin >> n;
    vector<int> par(n);
    for (auto& x: par) cin >> x;
    int sum = 0;
    for (auto& x: par) {
      if (x != -1) sum = (sum + x) % n;
    }
    int idx = find(par.begin(), par.end(), -1) - par.begin();
    par[idx] = (n-sum)%n;
    for (int i = 1; i < n; i++) cout << par[i]+1 << ' ' << i+1 << '\n';
  }
}
