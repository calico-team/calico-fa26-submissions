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
  for(int i = 0; i < r; i++) {
    for(int j = 0; j < c; j++) {
      int id = i*c+j;
      if(g[i][j] == '.') {
        dsu.merge(id, id+r*c);
      }
      for(int k = 0; k < 4; k++) {
        int nx = i + dx[k];
        int ny = j + dy[k];
        if(nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
        if(g[i][j] == '.' && g[nx][ny] == '.') {
          dsu.merge(i*c+j, nx*c+ny);
        }
        if(g[i][j] == '.' && g[nx][ny] == 'B') {
          dsu.merge(i*c+j, nx*c+ny);
        }
        if(g[i][j] == 'B' && g[nx][ny] == '.') {
          dsu.merge(i*c+j, nx*c+ny);
        }
        if(g[i][j] == 'B' && g[nx][ny] == 'B') {
          dsu.merge(i*c+j, nx*c+ny);
        }
        if(g[i][j] == '.' && g[nx][ny] == '.') {
          dsu.merge(i*c+j+r*c, nx*c+ny+r*c);
        }
        if(g[i][j] == '.' && g[nx][ny] == 'R') {
          dsu.merge(i*c+j+r*c, nx*c+ny+r*c);
        }
        if(g[i][j] == 'R' && g[nx][ny] == '.') {
          dsu.merge(i*c+j+r*c, nx*c+ny+r*c);
        }
        if(g[i][j] == 'R' && g[nx][ny] == 'R') {
          dsu.merge(i*c+j+r*c, nx*c+ny+r*c);
        }
      }
    }
  }
  while(q--) {
    int xa, ya, xb, yb;
    cin >> xa >> ya >> xb >> yb;
    if(dsu.find(xa*c+ya) == dsu.find(xb*c+yb)) {
      cout << "YES\n";
      continue;
    }
    if(dsu.find(xa*c+ya) == dsu.find(xb*c+yb+r*c)) {
      cout << "YES\n";
      continue;
    }
    else cout << "NO\n";
  }
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
