#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long
#define pb push_back
#define mp make_pair
#define endl '\n'
#define f first
#define s second
#define INF 0x3f3f3f3f
#define fileio(file) freopen(file ".in", "r", stdin); freopen(file ".out", "w", stdout)
#define pout(v); for (auto i : v) {cout << i << " ";} cout << endl;
#define FOR(i, n, m) for (int i = (n); i < (m); i++)
#define ROF(i, n, m) for (int i = (n); i > (m); i--)
const int MAXN = 1e1+1;
const int MAXM = 4e3+3;

int QQ;

int N, M, Q;
int m[MAXN][MAXM];

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

bool ok(tuple<int, int, int> curr) {
  int r = get<0>(curr), c = get<1>(curr), state = get<2>(curr);
  return r > -1 && r < N && c > -1 && c < M
    && (m[r][c] == -1 || m[r][c] == state);
}

int fastest(pair<int, int> a, pair<int, int> b) {
  // row, col, state
  vector<vector<vector<int>>> dp(N, vector<vector<int>>(M, vector<int>(2, -1)));
  queue<tuple<int, int, int>> q;
  dp[a.f][a.s][0] = 0;
  q.push(make_tuple(a.f, a.s, 0));

  while(!q.empty()) {
    tuple<int, int, int> curr = q.front(); q.pop();
    int currt = dp[get<0>(curr)][get<1>(curr)][get<2>(curr)];
    if (get<0>(curr) == b.f && get<1>(curr) == b.s) return currt; // at dest

    // walk
    FOR(i, 0, 4) {
      tuple<int, int, int> next = curr;
      get<0>(next) += dx[i];
      get<1>(next) += dy[i];
      if (!ok(next)) continue;
      int& currdp = dp[get<0>(next)][get<1>(next)][get<2>(next)];
      if (currdp == -1) {
        currdp = currt + 1;
        q.push(next);
      }
    }

    // spin
    if (m[get<0>(curr)][get<1>(curr)] == -1) {
      int toggle = 1 - get<2>(curr);
      int& toggledp = dp[get<0>(curr)][get<1>(curr)][toggle];
      if (toggledp == -1) {
        toggledp = currt+1;
        q.push(make_tuple(get<0>(curr), get<1>(curr), toggle));
      }
    }
  }

  return -1;
}

void solve() {
  memset(m, 0, sizeof m);
  cin >> N >> M >> Q;
  string _s;
  FOR(i, 0, N) {
    cin >> _s;
    FOR(j, 0, _s.length()) {
      if (_s[j] == '.') m[i][j] = -1;
      else if (_s[j] == 'B') m[i][j] = 0;
      else m[i][j] = 1;
    }
  }

  while(Q--) {
    pair<int, int> a, b;
    int K;
    cin >> a.f >> a.s >> b.f >> b.s >> K;
    int t = fastest(a, b);
    cout << ((t != -1 && t <= K) ? "YES" : "NO") << endl;
  }
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);

  cin >> QQ;
  while(QQ--) solve();

  return 0;
}
