#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// thanks gena
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 67
#endif
// END NO SAD

// BEGIN NO SAD
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define lb lower_bound
#define ub upper_bound
typedef vector<int> vi;
#define f first
#define s second
#define derr if(1) cerr

template<class Fun>
class y_combinator_result {
  Fun fun_;
public:
  template<class T>
  explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

  template<class ...Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

template<class T>
bool updmin(T& a, T b) {
  if(b < a) {
    a = b;
    return true;
  }
  return false;
}
template<class T>
bool updmax(T& a, T b) {
  if(b > a) {
    a = b;
    return true;
  }
  return false;
}
typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;

struct disjoint_set {
  vector<int> p, sz;
  disjoint_set(int n) {
    p.assign(n, -1);
    sz.assign(n, 1);
  }
  int find(int x) {
    return p[x] < 0 ? x : (p[x] = find(p[x]));
  }
  int getsz(int x) {
    return sz[find(x)];
  }
  bool merge(int x, int y) {
    // x goes to y
    x = find(x);
    y = find(y);
    if(x == y) return false;
    p[x] = y;
    sz[y] += sz[x];
    return true;
  }
};

int dx[4]{-1,0,1,0};
int dy[4]{0,1,0,-1};
void rsolve() {
  int r, c, q;
  cin >> r >> c >> q;
  vector<string> g(r);
  for(auto& x: g) cin >> x;
  disjoint_set dsu(2*r*c);
  vector<vector<int>> edges(2*r*c);
  auto addedge = [&](int i, int j) -> void {
    edges[i].pb(j);
    edges[j].pb(i);
  };
  for(int i = 0; i < r; i++) {
    for(int j = 0; j < c; j++) {
      int id = i*c+j;
      if(g[i][j] == '.') {
        addedge(id, id+r*c);
      }
      for(int k = 0; k < 4; k++) {
        int nx = i + dx[k];
        int ny = j + dy[k];
        if(nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
        if(g[i][j] == '.' && g[nx][ny] == '.') {
          addedge(i*c+j, nx*c+ny);
        }
        if(g[i][j] == '.' && g[nx][ny] == 'B') {
          addedge(i*c+j, nx*c+ny);
        }
        if(g[i][j] == 'B' && g[nx][ny] == '.') {
          addedge(i*c+j, nx*c+ny);
        }
        if(g[i][j] == 'B' && g[nx][ny] == 'B') {
          addedge(i*c+j, nx*c+ny);
        }
        if(g[i][j] == '.' && g[nx][ny] == '.') {
          addedge(i*c+j+r*c, nx*c+ny+r*c);
        }
        if(g[i][j] == '.' && g[nx][ny] == 'R') {
          addedge(i*c+j+r*c, nx*c+ny+r*c);
        }
        if(g[i][j] == 'R' && g[nx][ny] == '.') {
          addedge(i*c+j+r*c, nx*c+ny+r*c);
        }
        if(g[i][j] == 'R' && g[nx][ny] == 'R') {
          addedge(i*c+j+r*c, nx*c+ny+r*c);
        }
      }
    }
  }
  vector<bool> retv(q);
  vector<array<int, 6>> queriesv(q);
  for(int i = 0; i < q; i++) {
    for(int j = 0; j < 5; j++) cin >> queriesv[i][j];
    queriesv[i][5] = i;
  }
  auto dnc = y_combinator([&](auto self, int lhsc, int rhsc, vector<array<int, 6>>& currqueries) -> void {
    if(lhsc > rhsc) return;
    int midc = (lhsc+rhsc)/2;
    // row of midc -> everything else
    vector<vector<int>> distg(2*r);
    int nc = rhsc - lhsc + 1;
    // dp[coord] -> global id
    auto coordtoid = [&](int coord) -> int {
      int ret = 0;
      if(coord >= nc * r) {
        coord -= nc * r;
        ret += r*c;
      }
      assert(coord >= 0 && coord < nc*r);
      int crow = coord / nc;
      int ccol = coord % nc;
      ret += crow * c;
      ret += ccol + lhsc;
      return ret;
    };
    auto idtocoord = [&](int id) -> int {
      int ret = 0;
      if(id >= r*c) {
        id -= r*c;
        ret += nc * r;
      }
      int crow = id / c;
      int ccol = id % c;
      if(!(ccol >= lhsc && ccol <= rhsc)) {
        return -1;
      }
      ret += crow * nc;
      ret += ccol - lhsc;
      return ret;
    };
    int stress = 0;
    debug(lhsc, rhsc);
    for(int flag = 0; false && flag < 2; flag++) {
      for(int i = 0; i < r; i++) {
        for(int j = lhsc; j <= rhsc; j++) {
          int id = flag * r * c + i * c + j;
          debug(flag, i, j, id, stress);
          debug(idtocoord(id), coordtoid(stress));
          assert(idtocoord(id) == stress);
          assert(coordtoid(stress) == id);
          stress++;
        }
      }
    }
    for(int flag = 0; flag < 2; flag++) {
      for(int i = 0; i < r; i++) {
        int id = i * c + midc + (flag * r * c);
        vector<int>& dp = distg[flag*r+i];
        dp.assign(2*nc*r, 1e9);
        queue<int> q; // COORDS
        dp[idtocoord(id)] = 0;
        q.push(idtocoord(id));
        while(sz(q)) {
          int coord = q.front(); q.pop();
          int gid = coordtoid(coord);
          for(int out: edges[gid]) {
            int ncoord = idtocoord(out);
            if(ncoord < 0) continue;
            if(updmin(dp[ncoord], dp[coord]+1)) q.push(ncoord);
          }
        }
      }
    }
    if(lhsc == 5 && rhsc == 8) {
      debug(distg[0]);
    }
    vector<array<int, 6>> lhsquery, rhsquery;
    for(auto [xa, ya, xb, yb, k, qidx]: currqueries) {
      for(int i = 0; i < 2*r; i++) {
        // blue side
        int scoord = idtocoord(xa*c+ya);
        int tcoord1 = idtocoord(xb*c+yb);
        int tcoord2 = idtocoord(xb*c+yb+r*c);
        debug(i, lhsc, rhsc, distg[i][scoord], distg[i][tcoord1], distg[i][tcoord2]);
        if(distg[i][scoord] + distg[i][tcoord1] <= k) retv[qidx] = true;
        if(distg[i][scoord] + distg[i][tcoord2] <= k) retv[qidx] = true;
      }
      for(int i = 0; false && i < r; i++) {
        // red side
        int scoord = idtocoord(xa*c+ya+r*c);
        int tcoord1 = idtocoord(xb*c+yb);
        int tcoord2 = idtocoord(xb*c+yb+r*c);
        if(distg[i][scoord] + distg[i][tcoord1] <= k) retv[qidx] = true;
        if(distg[i][scoord] + distg[i][tcoord2] <= k) retv[qidx] = true;
      }
      if(max(ya, yb) < midc) lhsquery.pb({xa, ya, xb, yb, k, qidx});
      if(min(ya, yb) > midc) rhsquery.pb({xa, ya, xb, yb, k, qidx});
    }
    self(lhsc, midc-1, lhsquery);
    self(midc+1, rhsc, rhsquery);
  });
  dnc(0, c-1, queriesv);
  for(int i = 0; i < q; i++) if(retv[i]) cout << "YES\n"; else cout << "NO\n";
}

void solve() {
  int t = 1;
  cin >> t;
  while(t--) rsolve();
}

// what would chika do
// are there edge cases (N=1?)
// are array sizes proper (scaled by proper constant, for example 2* for koosaga tree)
// integer overflow?
// are you doing geometry in floating points
// have you tried rereading the problem statement

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
}
