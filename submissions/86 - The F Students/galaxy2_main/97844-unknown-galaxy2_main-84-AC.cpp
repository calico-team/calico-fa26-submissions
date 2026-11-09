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

enum S { R, B };

void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  auto c = [&](int x, int y, S s) { return 2 * (m * y + x) + s; };
  int N = n * m * 2;
  vector<vector<int>> adj(N);
  auto add = [&](int u, int v) { adj[u].push_back(v); };
  vector<string> a(n);
  for (string& s : a) cin >> s;
  for (int x = 0; x < m; ++x)
    for (int y = 0; y < n; ++y) {
      char start = a[y][x];
      for (auto [dx, dy] : dir) {
        int nx = x + dx, ny = y + dy;
        if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
        char end = a[ny][nx];
        if (start == '.') {
          add(c(x, y, B), c(x, y, R));
          add(c(x, y, R), c(x, y, B));
          if (end == '.')
            add(c(x, y, B), c(nx, ny, B)), add(c(x, y, R), c(nx, ny, R));
          else if (end == 'R')
            add(c(x, y, R), c(nx, ny, R));
          else
            add(c(x, y, B), c(nx, ny, B));
        } else if (start == 'R') {
          if (end != 'B') add(c(x, y, R), c(nx, ny, R));
        } else {
          if (end != 'R') add(c(x, y, B), c(nx, ny, B));
        }
      }
    }

  vector<vector<vector<int>>> dist(4 * m);
  auto dfs = [&](auto&& dfs, int u, int l, int r) -> void {
    int mid = (l + r) / 2, w = r - l + 1;
    auto vv = [&](int x) {
      return 2 * (w * ((x / 2) / m) + (x / 2) % m - l) + (x & 1);
    };
    dist[u].resize(2 * n);
    for (int y = 0; y < n; ++y)
      for (S s : {R, B}) {
        if (a[y][mid] != '.' && a[y][mid] != (s == R ? 'R' : 'B')) continue;
        auto& d = dist[u][2 * y + s];
        d.assign(2 * n * w, INT_MAX);
        int R = c(mid, y, s);
        queue<int> q;
        q.push(R);
        d[vv(R)] = 0;
        while (!q.empty()) {
          int u = q.front();
          q.pop();
          int i = vv(u);
          for (int v : adj[u]) {
            int x = (v / 2) % m;
            if (x < l || x > r) continue;
            int j = vv(v);
            if (d[j] != INT_MAX) continue;
            d[j] = d[i] + 1;
            q.push(v);
          }
        }
      }
    if (l < mid) dfs(dfs, u * 2, l, mid - 1);
    if (mid < r) dfs(dfs, u * 2 + 1, mid + 1, r);
  };
  dfs(dfs, 1, 0, m - 1);

  auto get = [&](auto&& get, int u, int l, int r, int start, int end) -> int {
    int mid = (l + r) / 2, w = r - l + 1, ans = INT_MAX;
    int xs = (start / 2) % m, ys = (start / 2) / m, xe = (end / 2) % m,
        ye = (end / 2) / m;
    int s = 2 * (w * ys + xs - l) + (start & 1),
        e = 2 * (w * ye + xe - l) + (end & 1);
    for (auto& d : dist[u]) {
      if (d.empty()) continue;
      int ds = d[s], de = d[e];
      if (ds == INT_MAX || de == INT_MAX) continue;
      ans = min(ans, ds + de);
    }
    if (xs < mid && xe < mid)
      ans = min(ans, get(get, u * 2, l, mid - 1, start, end));
    else if (xs > mid && xe > mid)
      ans = min(ans, get(get, u * 2 + 1, mid + 1, r, start, end));
    return ans;
  };

  while (q--) {
    int ys, xs, ye, xe, k;
    cin >> ys >> xs >> ye >> xe >> k;
#define yes cout << "YES\n"
#define no cout << "NO\n"
    bool ok = 0;
    if (a[ye][xe] == 'B')
      ok = get(get, 1, 0, m - 1, c(xs, ys, B), c(xe, ye, B)) <= k;
    else if (a[ye][xe] == 'R')
      ok = get(get, 1, 0, m - 1, c(xs, ys, B), c(xe, ye, R)) <= k;
    else
      ok = get(get, 1, 0, m - 1, c(xs, ys, B), c(xe, ye, R)) <= k ||
           get(get, 1, 0, m - 1, c(xs, ys, B), c(xe, ye, B)) <= k;
    if (ok)
      yes;
    else
      no;
  }
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