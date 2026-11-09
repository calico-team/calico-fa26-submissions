#include <bits/stdc++.h>
using namespace std;

const int N = 1e6+5;
int flsqrt[N];

int main () {
  ios_base::sync_with_stdio(0); cin.tie(0);
  for (int i = 1; i < N; i++) {
    flsqrt[i] = flsqrt[i-1];
    while ((flsqrt[i]+1)*(flsqrt[i]+1) <= i) flsqrt[i]++;
  }

  int T;
  cin >> T;
  while (T--) {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> a(n, vector<int>(m));
    vector<vector<int>> r(n, vector<int>(m+1));
    for (int i = 0; i < n; i++) iota(r[i].begin(), r[i].end(), 0);
    vector<tuple<int, int, int>> quakes(q);
    for (auto& [x, y, p]: quakes) cin >> x >> y >> p;
    reverse(quakes.begin(), quakes.end());
    for (auto& [x, y, p]: quakes) {
      for (int i = -p; i <= p; i++) {
        // i^2+j^2 <= p^2
        // j <= sqrt(p^2-i^2)
        int d = flsqrt[p*p-i*i];
        for (int yj = y-d; yj <= y+d; yj = r[x+i][yj]) {
          if (a[x+i][yj] == 0) {
            a[x+i][yj] = p*p+1-i*i-(yj-y)*(yj-y);
            r[x+i][yj] = r[x+i][yj+1];
          }
          else {
            r[x+i][yj] = r[x+i][r[x+i][yj]];
          }
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << a[i][j] << ' ';
      }
      cout << '\n';
    }
  }
}
