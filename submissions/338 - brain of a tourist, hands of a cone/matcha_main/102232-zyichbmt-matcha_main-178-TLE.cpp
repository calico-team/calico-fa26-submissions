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
  vector<array<int, 2>> v; // <
  v.pb({0, 0});
  int pref = 0;
  int rmax = 0;
  for(int i = 0; i < n; i++) {
    int bbit = -1;
    for(int bit = 29; bit >= 0; bit--) {
      if(lv[i] & (1 << bit)) {
        pref ^= 1 << bit;
        lv[i] ^= 1 << bit;
        rv[i] ^= 1 << bit;
      }
      else if(rv[i] & (1 << bit)) {
        bbit = bit;
        break;
      }
    }
    updmax(rmax, (1 << bbit) - 1);
    pref ^= rv[i];
  }
  sort(all(v), [&](auto a, auto b) -> bool {
    return (a[1] - a[0]) > (b[1] - b[0]);
  });
  array<int, 30> used; used.fill(0);
  int ret = 0;
  for(int i = 0; i < n; i++) {
    int bbit = -1;
    for(int bit = 29; bit >= 0; bit--) {
      if(lv[i] & (1 << bit)) {
        pref ^= 1 << bit;
        lv[i] ^= 1 << bit;
        rv[i] ^= 1 << bit;
      }
      else if(rv[i] & (1 << bit)) {
        bbit = bit;
        break;
      }
    }
    vector<array<int, 2>> nv;
    int rseen = (1 << bbit);
    for(int x = bbit-1; x >= 0; x--) {
      if(rv[i] & (1 << x)) {
        array<int, 2> nxt = {rseen, rseen + (1 << x) - 1};
        for(auto x: v) {
          array<int, 2> y;
          y[0] = x[0] ^ nxt[0];
          int aux1 = max(x[1] - x[0], nxt[1] - nxt[0]);
          y[0] -= y[0] & aux1;
          y[1] = y[0] + aux1;
          nv.pb(y);
          // [x[0], x[1]]
          // [nxt[0], nxt[1]]
        }
        rseen |= 1 << x;
      }
    }
    assert(rseen == rv[i]);
    int lseen = 0;
    for(int x = bbit-1; x >= 0; x--) {
      if((lv[i] & (1 << x)) == 0) {
        array<int, 2> nxt = {lseen + (1 << x), lseen + (2 << x) - 1};
        for(auto x: v) {
          array<int, 2> y;
          y[0] = x[0] ^ nxt[0];
          int aux1 = max(x[1] - x[0], nxt[1] - nxt[0]);
          y[0] -= y[0] & aux1;
          y[1] = y[0] + aux1;
          nv.pb(y);
          // [x[0], x[1]]
          // [nxt[0], nxt[1]]
        }
      }
      else lseen |= 1 << x;
    }
    assert(lseen == lv[i]);
    {
      array<int, 2> nxt = {lseen, lseen};
      for(auto x: v) {
        array<int, 2> y;
        y[0] = x[0] ^ nxt[0];
        int aux1 = max(x[1] - x[0], nxt[1] - nxt[0]);
        y[0] -= y[0] & aux1;
        y[1] = y[0] + aux1;
        nv.pb(y);
        // [x[0], x[1]]
        // [nxt[0], nxt[1]]
      }
    }
    {
      array<int, 2> nxt = {rseen, rseen};
      for(auto x: v) {
        array<int, 2> y;
        y[0] = x[0] ^ nxt[0];
        int aux1 = max(x[1] - x[0], nxt[1] - nxt[0]);
        y[0] -= y[0] & aux1;
        y[1] = y[0] + aux1;
        nv.pb(y);
        // [x[0], x[1]]
        // [nxt[0], nxt[1]]
      }
    }
    sort(all(nv), [&](auto a, auto b) -> bool {
      if(a[0] != b[0]) return a[0] < b[0];
      return a[1] > b[1];
    });
    {
      vector<array<int, 2>> st;
      for(int i = 0; i < sz(nv); i++) {
        if(sz(st) == 0 || nv[i][0] > st.back()[1]) st.pb(nv[i]);
      }
      swap(st, nv);
    }
    {
      vector<array<int, 2>> st;
      for(int i = 0; i < sz(nv); i++) {
        st.pb(nv[i]);
        while(sz(st) >= 2) {
          auto [a, b] = st[sz(st)-1];
          auto [c, d] = st[sz(st)-2];
          if(d+1 == a && d-c == b-a) {
            st.pop_back();
            st.pop_back();
            st.pb({c, b});
          }
          else break;
        }
      }
      swap(st, nv);
    }
    swap(v, nv);
    pref = pref ^ rv[i];
    for(auto [lhs, rhs]: v) {
      int e = pref ^ lhs;
      int sz = rhs - lhs;
      e = e | sz;
      updmax(ret, e);   
    }
    if((ret&rmax) == rmax) break;
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
