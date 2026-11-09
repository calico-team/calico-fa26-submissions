#pragma region template
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using ll = long long;
using ull = unsigned long long;
#define ceil(n, m) (((n) + (m) - 1) / (m))
#define sub(a, b, m) (((a % m) - (b % m) + m) % m)
#define all(vec) vec.begin(), vec.end()
#define rall(vec) vec.rbegin(), vec.rend()
#define fi first
#define se second
#define _ ' '
#define endl '\n'

template <class A, class B>
struct Pair {
  A x;
  B y;

  constexpr Pair() : x(), y() {}
  constexpr Pair(const A& a, const B& b) : x(a), y(b) {}

  template <class U1, class U2>
  constexpr Pair(U1&& a, U2&& b)
      : x(std::forward<U1>(a)), y(std::forward<U2>(b)) {}

  template <class U1, class U2>
  constexpr Pair(const Pair<U1, U2>& p) : x(p.x), y(p.y) {}

  template <class U1, class U2>
  constexpr Pair(Pair<U1, U2>&& p)
      : x(std::forward<U1>(p.x)), y(std::forward<U2>(p.y)) {}

  template <class U1, class U2>
  constexpr Pair(const std::pair<U1, U2>& p) : x(p.first), y(p.second) {}

  template <class U1, class U2>
  constexpr Pair(std::pair<U1, U2>&& p)
      : x(std::forward<U1>(p.first)), y(std::forward<U2>(p.second)) {}

  constexpr Pair(const Pair&) = default;
  constexpr Pair(Pair&&) = default;
  constexpr Pair& operator=(const Pair&) = default;
  constexpr Pair& operator=(Pair&&) = default;

  template <class U1, class U2>
  constexpr Pair& operator=(const std::pair<U1, U2>& p) {
    x = p.first;
    y = p.second;
    return *this;
  }

  template <class U1, class U2>
  constexpr Pair& operator=(std::pair<U1, U2>&& p) {
    x = std::forward<U1>(p.first);
    y = std::forward<U2>(p.second);
    return *this;
  }

  constexpr operator std::pair<A, B>() const { return {x, y}; }

  constexpr void swap(Pair& other) noexcept(noexcept(std::swap(x, other.x)) &&
                                            noexcept(std::swap(y, other.y))) {
    using std::swap;
    swap(x, other.x);
    swap(y, other.y);
  }

  friend constexpr bool operator==(const Pair& a, const Pair& b) {
    return a.x == b.x && a.y == b.y;
  }
  friend constexpr bool operator!=(const Pair& a, const Pair& b) {
    return !(a == b);
  }
  friend constexpr bool operator<(const Pair& a, const Pair& b) {
    return (a.x < b.x) || (!(b.x < a.x) && a.y < b.y);
  }
  friend constexpr bool operator>(const Pair& a, const Pair& b) {
    return b < a;
  }
  friend constexpr bool operator<=(const Pair& a, const Pair& b) {
    return !(b < a);
  }
  friend constexpr bool operator>=(const Pair& a, const Pair& b) {
    return !(a < b);
  }
};

template <class A, class B>
Pair(A, B) -> Pair<A, B>;

template <std::size_t I, class A, class B>
constexpr auto& get(Pair<A, B>& p) noexcept {
  static_assert(I < 2);
  if constexpr (I == 0)
    return p.x;
  else
    return p.y;
}

template <std::size_t I, class A, class B>
constexpr const auto& get(const Pair<A, B>& p) noexcept {
  static_assert(I < 2);
  if constexpr (I == 0)
    return p.x;
  else
    return p.y;
}

template <std::size_t I, class A, class B>
constexpr auto&& get(Pair<A, B>&& p) noexcept {
  static_assert(I < 2);
  if constexpr (I == 0)
    return std::move(p.x);
  else
    return std::move(p.y);
}

template <std::size_t I, class A, class B>
constexpr const auto&& get(const Pair<A, B>&& p) noexcept {
  static_assert(I < 2);
  if constexpr (I == 0)
    return std::move(p.x);
  else
    return std::move(p.y);
}

namespace std {
template <class A, class B>
struct tuple_size<Pair<A, B>> : integral_constant<size_t, 2> {};

template <class A, class B>
struct tuple_element<0, Pair<A, B>> {
  using type = A;
};

template <class A, class B>
struct tuple_element<1, Pair<A, B>> {
  using type = B;
};

template <class A, class B>
struct hash<Pair<A, B>> {
  size_t operator()(const Pair<A, B>& p) const {
    size_t h1 = std::hash<A>{}(p.x);
    size_t h2 = std::hash<B>{}(p.y);
    return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
  }
};
};  // namespace std

#define pair Pair

template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

pair<int, int> dir[]{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
pair<int, int> diag[]{
    {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1},
};

template <typename T>
istream& operator>>(istream& in, vector<T>& v) {
  for (T& x : v) in >> x;
  return in;
}

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
  for (const T& x : v) out << x << ' ';
  return out;
}

#ifdef LOCAL
#include "../tools/debug.h"
#else
#define DBG(...)
#define CHK(...)
#endif

#pragma endregion template

constexpr int MOD = 998244353, N = 2e5 + 67;

struct BinaryTrie {
  static const int B = 30;   // values must satisfy 0 <= v < 2^30
  vector<array<int, 2>> nx;  // nx[u][bit] = child index, 0 = none
  vector<int> cnt;  // cnt[u] = how many inserted numbers pass through u

  BinaryTrie() {
    nx.push_back({0, 0});  // root at index 0
    cnt.push_back(0);
  }

  void insert(int v) {
    int u = 0;
    for (int b = B - 1; b >= 0; b--) {
      int c = (v >> b) & 1;
      if (!nx[u][c]) {
        nx[u][c] = (int)nx.size();
        nx.push_back({0, 0});
        cnt.push_back(0);
      }
      u = nx[u][c];
      cnt[u]++;
    }
  }

  // Removes one copy of v; v must have been inserted.
  void erase(int v) {
    int u = 0;
    for (int b = B - 1; b >= 0; b--) {
      int c = (v >> b) & 1;
      u = nx[u][c];
      cnt[u]--;
    }
  }

  // Maximum of (v ^ y) over all stored y. The trie must be non-empty.
  int maxXor(int v) const {
    int u = 0, res = 0;
    for (int b = B - 1; b >= 0; b--) {
      int c = (v >> b) & 1;
      int want = c ^ 1;
      int w = nx[u][want];
      if (w && cnt[w] > 0) {
        res |= (1 << b);
        u = w;
      } else {
        u = nx[u][c];
      }
    }
    return res;
  }
};

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  vector<ll> v(n);
  for (int& x : a) cin >> x, --x;
  for (ll& x : v) cin >> x;

  vector<vector<int>> into(n);
  vector<int> inval(n);
  for (int i = 0; i < n; ++i) into[a[i]].push_back(i), ++inval[a[i]];
  queue<int> q;
  for (int i = 0; i < n; ++i)
    if (!inval[i]) q.push(i);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    int v = a[u];
    if (!--inval[v]) q.push(v);
  }

  vector<bool> vis(n);
  vector<optional<BinaryTrie>> bts(n);
  vector<int> cycowner(n, -1), cycowners;
  vector<int> prefbefore(n, -1);
  for (int i = 0; i < n; ++i) {
    if (!inval[i] || vis[i]) continue;
    vector<int> cyc;
    int u = i, owner = i;
    cycowners.push_back(owner);
    int pref = 0;
    while (!vis[u]) {
      vis[u] = 1;
      cyc.push_back(u);
      cycowner[u] = owner;
      prefbefore[u] = pref;
      pref ^= v[u];
      u = a[u];
    }
    bts[owner] = BinaryTrie{};
    pref = 0;
    (*bts[owner]).insert(0);
    for (int& x : cyc) (*bts[owner]).insert(pref ^= v[x]);
    for (int& x : cyc) (*bts[owner]).insert(pref ^= v[x]);
  }

  BinaryTrie gtrie;
  gtrie.insert(0);
  fill(all(vis), 0);
  vector<int> ans(n, -1);
  int pref = 0, src = -1;
  auto dfs = [&](auto&& dfs, int u) -> void {
    if (!inval[u]) {
      ans[u] = max(gtrie.maxXor(pref),
                   (*bts[cycowner[src]]).maxXor(pref ^ prefbefore[src]));
    }
    vis[u] = 1;
    for (int to : into[u]) {
      if (inval[to]) continue;
      assert(!vis[to]);
      pref ^= v[to];
      gtrie.insert(pref);
      dfs(dfs, to);
      gtrie.erase(pref);
      pref ^= v[to];
    }
  };

  for (int i = 0; i < n; ++i)
    if (inval[i]) {
      ans[i] = (*bts[cycowner[i]]).maxXor(prefbefore[i]);
      src = i;
      dfs(dfs, i);
    }

  for (int& x : ans) cout << x << _;
  cout << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tc = 1;
  cin >> tc;
  for (int t = 1; t <= tc; t++) {
    // cout << "Case #" << t << ": ";
    solve();
  }
}