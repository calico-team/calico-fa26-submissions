#include <bits/stdc++.h>
using namespace std;

class dsu {
  public:
    vector<int> parents;
    vector<int> sizes;
    dsu (int n) {
      parents.resize(n);
      iota(parents.begin(), parents.end(), 0);
      sizes.resize(n, 1);
    }
    int root(int u) {
      return parents[u] == u ? u : parents[u] = root(parents[u]);
    }
    bool join(int u, int v) {
      int a = root(u);
      int b = root(v);
      if (a == b) return 0;
      if (sizes[a] > sizes[b]) swap(a, b);
      parents[a] = b;
      sizes[b] += sizes[a];
      return 1;
    }
};

int main () {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> mask(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
      string row;
      cin >> row;
      for (int j = 0; j < m; j++) {
        if (row[j] == '.') mask[i][j] = 3;
        else if (row[j] == 'R') mask[i][j] = 1;
        else if (row[j] == 'B') mask[i][j] = 2;
      }
    }
    dsu D(2*n*m);
    auto get = [&] (int i, int j, int k) {
      return 2*(m*i+j)+k;
    };
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (mask[i][j] == 3) D.join(get(i, j, 0), get(i, j, 1));
      }
    }
    for (int c = 1; c <= 2; c++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          if (i+1 < n && (mask[i][j]&mask[i+1][j]&c)) D.join(get(i, j, c-1), get(i+1, j, c-1));
          if (j+1 < m && (mask[i][j]&mask[i][j+1]&c)) D.join(get(i, j, c-1), get(i, j+1, c-1));
        }
      }
    }

    while (q--) {
      int sx, sy, tx, ty;
      cin >> sx >> sy >> tx >> ty;
      int cs = (mask[sx][sy]&1 ? 0 : 1);
      int ct = (mask[tx][ty]&1 ? 0 : 1);
      cout << (D.root(get(sx, sy, cs)) == D.root(get(tx, ty, ct)) ? "YES" : "NO") << '\n';
    }
  }
}
