/*

*/

#include <bits/stdc++.h>

namespace kactl {

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

/**
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: $O(\alpha(N))$
 */
struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b]; e[b] = a;
    return true;
  }
};

}

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> v2i;
typedef std::vector<v2i> v3i;
typedef std::vector<ll> vll;
#define va(type, sz) std::vector<std::array<type, sz>>
#define v2a(type, sz) std::vector<va(type, sz)>
#define setmax(a, b) a = std::max(a, b)
#define setmin(a, b) a = std::min(a, b)

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

  int tn = 1;
  std::cin >> tn; std::cerr << "\e[1;31m\e[5m[!]\e[25m MULTITEST MODE \e[5m[!]\e[25m\e[0m" << std::endl;
  while (tn--) {
    ll n, m, qn;
    std::cin >> n >> m >> qn;
    std::vector<std::string> a(n);
    for (auto &x : a) std::cin >> x;
    
    kactl::UF dsu(n*m);
    #define K(i, j) (i+j*n)
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        for (auto [di, dj] : va(int, 2) {
          /*adj */ {0,1},{1,0},{0,-1},{-1,0}
        }) {
          int ni = i + di, nj = j + dj;
          // valid coordinates: i in [0,n), j in [0,m)
          if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
          auto c = a[i][j];
          auto d = a[ni][nj];
          if (c == d || c == '.' || d == '.') dsu.join(K(i, j), K(ni, nj));
        }
      }
    }
    for (int i = 0; i < qn; ++i) {
      ll si, sj, ti, tj; // si sj ti tj
      std::cin >> si >> sj >> ti >> tj;
      int s = K(si, sj);
      int t = K(ti, tj);
      std::cout << (dsu.sameSet(s, t) ? "YES" : "NO") << std::endl;
    }

    // std::cout << std::endl;
  }
  return 0;
}