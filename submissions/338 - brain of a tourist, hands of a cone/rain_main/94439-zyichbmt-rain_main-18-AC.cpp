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

void rsolve() {
  int n, k;
  cin >> n >> k;
  vector<array<int, 3>> v(n); // <x, y, z, d>
  vector<char> dirv(n);
  for(int i = 0; i < n; i++) {
    cin >> v[i][0];
    cin >> v[i][1];
    cin >> v[i][2];
    cin >> dirv[i];
  }
  ll ret = n * (ll)k;
  map<int, vector<int>> dp;
  for(int i = 0; i < n; i++) dp[v[i][0]+v[i][1]].pb(i);
  for(auto& [kk, vv]: dp) {
    sort(all(vv), [&](auto a, auto b) -> bool {
      return v[a][0] < v[b][0];
    });
    vector<int> ex;
    ll npair = 0;
    int eidx = 0;
    for(int i = 0; i < sz(vv); i++) {
      int cx = v[vv[i]][0];
      if(dirv[vv[i]] == 'E') ex.pb(cx);
      else {
        while(eidx < sz(ex) && cx - ex[eidx] >= k) eidx++;
        npair += sz(ex) - eidx;
      }
    }
    ret -= npair;
  }
  cout << ret << "\n";
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
