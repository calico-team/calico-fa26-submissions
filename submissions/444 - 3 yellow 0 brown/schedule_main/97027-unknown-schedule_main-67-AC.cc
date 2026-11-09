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
const int MAXN = 1e4+4;

int Q;
vector<int> adj[MAXN];
int dmax = -1;
//  curr    
int cnt[MAXN];

void dfs(int cn, int d) {
  cnt[d]++;
  dmax = max(dmax, d);
  for(int vn : adj[cn]) dfs(vn, d+1);
}

void solve() {
  memset(adj, 0, sizeof adj);
  memset(cnt, 0, sizeof cnt);
  dmax = -1;

  int N, M, K;
  cin >> N >> M >> K;

  int pn, p[MAXN];
  FOR(i, 1, N+1) {
    cin >> p[i];
    if (p[i]) adj[p[i]].pb(i);
  }

  FOR(r, 1, N+1) if (!p[r]) dfs(r, 1);

  int ans = N, less = 0;
  FOR(sem, 1, min(M, dmax)+1) {
    ans = min(ans, less + K * (M-sem+1));
    less += cnt[sem];
  }
  ans = min(ans, less);
  cout << ans << endl;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);

  cin >> Q;

  while(Q--) solve();

  return 0;
}
