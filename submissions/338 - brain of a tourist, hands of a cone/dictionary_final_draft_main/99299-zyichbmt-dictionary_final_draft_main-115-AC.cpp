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

struct node {
  int nactive;
  node* zero;
  node* one;
};
node* makenode() {
  node* ret = new node;
  ret->nactive = 0;
  ret->zero = nullptr;
  ret->one = nullptr;
  return ret;
}
void ins(node* root, int val) {
  for(int i = 29; i >= 0; i--) {
    root->nactive++;
    if((val>>i)&1) {
      if(root->one == nullptr) root->one = makenode();
      root = root->one;
    }
    else {
      if(root->zero == nullptr) root->zero = makenode();
      root = root->zero;
    }
  }
  root->nactive++;
}
void erase(node* root, int val) {
  for(int i = 29; i >= 0; i--) {
    root->nactive--;
    if((val>>i)&1) {
      root = root->one;
    }
    else {
      root = root->zero;
    }
    assert(root != nullptr);
  }
  root->nactive--;
}
// returns max of (val ^ something in trie)
int qry(node* root, int val) {
  int ret = 0;
  for(int i = 29; i >= 0; i--) {
    if(root == nullptr) {
      assert(false);
    }
    if((val>>i) & 1) {
      if(root->zero && root->zero->nactive) {
        root = root->zero;
        ret |= 1 << i;
      }
      else {
        root = root->one;
      }
    }
    else {
      if(root->one && root->one->nactive) {
        root = root->one;
        ret |= 1 << i;
      }
      else {
        root = root->zero;
      }
    }
  }
  return ret;
}
void cleanse(node* n) {
  if(n == nullptr) return;
  cleanse(n->zero);
  cleanse(n->one);
  delete n;
}

void rsolve() {
  int n;
  cin >> n;
  vector<int> to(n);
  for(auto& x: to) {
    cin >> x; x--;
  }
  vector<vector<int>> children(n);
  for(int i = 0; i < n; i++) {
    children[to[i]].pb(i);
  }
  vector<ll> v(n);
  for(auto& x: v) cin >> x;
  vector<vector<int>> parv(n);
  vector<bool> seen(n);
  vector<int> rootv(n);
  vector<ll> dp(n);
  vector<ll> retv(n);
  for(int src = 0; src < n; src++) {
    if(seen[src]) continue;
    int a = to[src];
    int b = to[a];
    while(a != b) {
      a = to[a];
      b = to[to[b]];
    }
    int root = a;
    dp[root] = v[root];
    vector<int> subtreev;
    auto dfsfordp = y_combinator([&](auto self, int curr) -> void {
      assert(!seen[curr]);
      seen[curr] = true;
      subtreev.pb(curr);
      for(int out: children[curr]) {
        if(seen[out]) continue;
        dp[out] = dp[curr] ^ v[out];
        self(out);
      }
    }); dfsfordp(root);
    node* nroot = makenode();
    auto dfsforans = y_combinator([&](auto self, int curr) -> void {
      ins(nroot, dp[curr]);
      updmax(retv[curr], (ll)qry(nroot, dp[curr]));
      if(curr == to[root]) {
        for(int out: subtreev) {
          updmax(retv[out], (ll)qry(nroot, dp[out]));
          updmax(retv[out], (ll)qry(nroot, dp[out] ^ dp[curr]));
        }
      }
      for(int out: children[curr]) {
        if(out == root) continue;
        self(out);
      }
      erase(nroot, dp[curr]);
    }); dfsforans(root);
    cleanse(nroot);
  }
  for(int i = 0; i < n; i++) cout << retv[i] << " \n"[i == n-1];
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
