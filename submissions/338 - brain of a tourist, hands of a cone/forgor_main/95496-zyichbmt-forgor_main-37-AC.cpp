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

void solvefirst() {
  int n;
  cin >> n;
  vector<vector<int>> edges(n+1);
  for(int i = 0; i < n-1; i++) {
    int a, b;
    cin >> a >> b;
    edges[a].pb(b);
    edges[b].pb(a);
  }
  vector<int> parv(n+1, -1);
  auto dfs = y_combinator([&](auto self, int curr, int par) -> void {
    for(int out: edges[curr]) {
      if(out == par) continue;
      parv[out] = curr;
      self(out, curr);
    }
  }); dfs(1, -1);
  debug(parv);
  int sumv = 0;
  for(int i = 2; i <= n; i++) {
    sumv += parv[i];
    sumv %= n;
  }
  cout << sumv;
  for(int i = 2; i <= n; i++) cout << " " << parv[i];
  cout << "\n";
}
void solvesecond() {
  int n;
  cin >> n;
  vector<int> v(n+1);
  for(int i = 1; i <= n; i++) cin >> v[i];
  if(v[1] == -1);
  else {
    int tot = v[1];
    int bad = -1;
    for(int j = 2; j <= n; j++) {
      if(v[j] == -1) {
        bad = j;
        continue;
      }
      tot -= v[j];
      if(tot <= 0) tot += n;
    }
    assert(bad >= 2);
    v[bad] = tot;
  }
  for(int i = 2; i <= n; i++) cout << v[i] << " " << i << "\n";
}
void rsolve() {
  string phase;
  cin >> phase;
  if(phase == "FIRST") solvefirst();
  else solvesecond();
}

void solve() {
  int t = 1;
  // cin >> t;
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
