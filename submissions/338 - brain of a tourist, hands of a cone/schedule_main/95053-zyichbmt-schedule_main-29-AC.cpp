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
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> par(n+1);
  vector<int> cdeg(n+1);
  vector<vector<int>> children(n+1);
  for(int i = 1; i <= n; i++) {
    cin >> par[i];
    children[par[i]].pb(i);
    cdeg[par[i]]++;
  }
  vector<int> dp(n+1, 1e9);
  queue<int> q;
  for(int i = 1; i <= n; i++) {
    if(par[i] == 0) {
      dp[i] = 0;
      q.push(i);
    }
  }
  while(sz(q)) {
    int curr = q.front(); q.pop();
    for(int out: children[curr]) {
      dp[out] = dp[curr]+1;
      q.push(out);
    }
  }
  vector<int> freqv(n+1);
  for(int i = 1; i <= n; i++) freqv[dp[i]]++;
  int ret = 0;
  int s = 0;
  for(int i = 0; i < m; i++) {
    if(i < sz(freqv) && freqv[i]) {
      s += freqv[i];
    }
    int take = min(s, k);
    s -= take;
    ret += take;
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
