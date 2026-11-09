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
const int MAXQ = 1e5+5;

int QQ;

int N, M, Q;
int m[MAXN][MAXM];

pair<int, int> a[MAXQ], b[MAXQ];
int k[MAXQ];
int ans[MAXQ];

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

bool ok(tuple<int, int, int> curr, int ll, int rr) {
  int r = get<0>(curr), c = get<1>(curr), state = get<2>(curr);
  return r > -1 && r < N && c > ll-1 && c < rr+1
    && (m[r][c] == -1 || m[r][c] == state);
}

vector<vector<vector<int>>> fastest(tuple<int, int, int> src, int ll, int rr) {
  // row, col, state
  // vector<vector<vector<int>>> dp(N, vector<vector<int>>(M, vector<int>(2, -1)));
  vector<vector<vector<int>>> dp(N, vector<vector<int>>(rr-ll+1, {INF, INF}));
  queue<tuple<int, int, int>> q;
  // dp[a.f][a.s][0] = 0;
  // q.push(make_tuple(a.f, a.s, 0));
  dp[get<0>(src)][get<1>(src)-ll][get<2>(src)] = 0;
  q.push(src);

  while(!q.empty()) {
    tuple<int, int, int> curr = q.front(); q.pop();
    // int currt = dp[get<0>(curr)][get<1>(curr)][get<2>(curr)];
    // if (get<0>(curr) == b.f && get<1>(curr) == b.s) return currt; // at dest
    int currt = dp[get<0>(curr)][get<1>(curr)-ll][get<2>(curr)];

    // walk
    FOR(i, 0, 4) {
      tuple<int, int, int> next = curr;
      get<0>(next) += dx[i];
      get<1>(next) += dy[i];
      // if (!ok(next)) continue;
      // int& currdp = dp[get<0>(next)][get<1>(next)][get<2>(next)];
      // if (currdp == -1) {
      if (!ok(next, ll, rr)) continue;
      int& currdp = dp[get<0>(next)][get<1>(next)-ll][get<2>(next)];
      if (currdp == INF) {
        currdp = currt + 1;
        q.push(next);
      }
    }

    // spin
    if (m[get<0>(curr)][get<1>(curr)] == -1) {
      int toggle = 1 - get<2>(curr);
      // int& toggledp = dp[get<0>(curr)][get<1>(curr)][toggle];
      // if (toggledp == -1) {
      int& toggledp = dp[get<0>(curr)][get<1>(curr)-ll][toggle];
      if (toggledp == INF) {
        toggledp = currt+1;
        q.push(make_tuple(get<0>(curr), get<1>(curr), toggle));
      }
    }
  }

  return dp; 
}

void div(int ll, int rr, vector<int>& qs) {
  if (qs.empty()) return;
  int mid = (ll+rr)/2;
  vector<int> l, r;

  vector<vector<vector<vector<int>>>> splits;
  FOR(rw, 0, N) FOR(st, 0, 2) {
    tuple<int, int, int> split = make_tuple(rw, mid, st);
    if (ok(split, ll, rr)) splits.pb(fastest(split, ll, rr));
  }

  for(int q : qs) {
    for(vector<vector<vector<int>>>& d : splits) {
      int toa = d[a[q].f][a[q].s-ll][0];
      int tob = min(d[b[q].f][b[q].s-ll][0], d[b[q].f][b[q].s-ll][1]);
      ans[q] = min(ans[q], toa + tob);
    }
    if (a[q].s < mid && b[q].s < mid) l.pb(q);
    else if (a[q].s > mid && b[q].s > mid) r.pb(q);
  }

  div(ll, mid, l);
  div(mid+1, rr, r);
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

  vector<int> qs;
  FOR(i, 0, Q) {
    cin >> a[i].f >> a[i].s >> b[i].f >> b[i].s >> k[i];
    ans[i] = INF;
    qs.pb(i);
  }

  div(0, M-1, qs);

  FOR(i, 0, Q) cout << (ans[i] <= k[i] ? "YES" : "NO") << endl;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);

  cin >> QQ;
  while(QQ--) solve();

  return 0;
}
