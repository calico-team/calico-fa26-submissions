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

mt19937 g1(0x14004);
void rsolve() {
  int n;
  cin >> n;
  vector<int> lv(n), rv(n);
  for(auto& x: lv) cin >> x;
  for(auto& x: rv) cin >> x;
  set<int> dp;
  dp.insert(0);
  vector<int> ord(n);
  iota(all(ord), 0);
  shuffle(all(ord), g1);
  for(int i: ord) {
    set<int> ndp;
    for(int a = lv[i]; a <= lv[i] + 15 && a <= rv[i]; a++) {
      for(int out: dp) ndp.insert(out^a);
    }
    for(int a = rv[i]; a >= lv[i] && a >= rv[i] - 15; a--) {
      for(int out: dp) ndp.insert(out^a);
    }
    dp.clear();
    {
      int iter = 0;
      auto it = ndp.begin();
      while(iter++ < 16 && it != ndp.end()) {
        dp.insert(*it);
        it++;
      }
    }
    {
      int iter = 0;
      auto it = ndp.rbegin();
      while(iter++ < 16 && it != ndp.rend()) {
        dp.insert(*it);
        it++;
      }
    }
  }
  cout << *max_element(all(dp)) << "\n";
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
