#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

#define fi first
#define se second

typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;

constexpr int MAX_N = 1e5 + 9, MAX_L = 40;

constexpr ll INF = 1e18;

constexpr ll base = 233;
constexpr ll MOD = 1e9;

constexpr double EPS = 1e-8;
constexpr ll OFFSET = 1e5;

int n;
int r, a[MAX_N];

void solve() {
  std::cin >> n >> r;
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i];
  int cur = 0, cnt[2]{};
  for (int i = 1; i <= n; ++i) {
    int mor = a[i] - a[i - 1];
    if (cnt[0] > 0 && mor >= cnt[0]) {
      mor -= cnt[0];
      cnt[0] = 0;
      --cur;
      std::swap(cnt[0], cnt[1]);
      if (cnt[0] > 0 && mor >= cnt[0]) {
        mor -= cnt[0];
        cnt[0] = 0;
        --cur;
      }
    }

    if (cur == 2) {
      std::cout << "NO\n";
      return;
    }
    cnt[cur++] = r;
  }
  std::cout << "YES\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
