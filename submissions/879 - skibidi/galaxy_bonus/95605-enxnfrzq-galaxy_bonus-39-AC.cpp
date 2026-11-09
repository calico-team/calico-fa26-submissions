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

constexpr int MAX_N = 2e2 + 9, MAX_L = 40;

constexpr ll INF = 1e18;

constexpr ll base = 233;
constexpr ll MOD = 1e9;

constexpr double EPS = 1e-8;
constexpr ll OFFSET = 1e5;

int n, m, q;
int map[MAX_N][MAX_N];
int id[MAX_N][MAX_N], cnt_id;
bool vis[MAX_N][MAX_N];

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

void dfs(int x, int y) {

  // std::cout << x << ' ' << y << ' ' << map[x][y] << '\n';
  vis[x][y] = true;
  id[x][y] = cnt_id;
  for (int k = 0; k < 4; ++k) {
    int vx = x + dx[k], vy = y + dy[k];
    if (vis[vx][vy] || vx < 0 || vx >= n || vy < 0 || vy >= m)
      continue;
    if (map[x][y] == 0 || map[vx][vy] == 0)
      dfs(vx, vy);
    else if (map[x][y] == map[vx][vy])
      dfs(vx, vy);
  }
}

void solve() {
  std::cin >> n >> m >> q;
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    for (int j = 0; j < m; ++j) {
      int &x = map[i][j];
      if (s[j] == '.')
        x = 0;
      else if (s[j] == 'R')
        x = 1;
      else
        x = 2;
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (!vis[i][j]) {
        ++cnt_id;
        dfs(i, j);
      }
    }
  }

  while (q--) {
    int lx, ly, rx, ry;
    std::cin >> lx >> ly >> rx >> ry;
    std::cout << (id[lx][ly] == id[rx][ry] ? "YES" : "NO") << '\n';
  }

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      vis[i][j] = id[i][j] = 0;
  cnt_id = 0;
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
