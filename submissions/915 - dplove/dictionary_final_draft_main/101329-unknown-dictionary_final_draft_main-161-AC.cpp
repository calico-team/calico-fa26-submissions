#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<climits>
#include<string>
#include<numeric>
#include<deque>
using namespace std;

#define int long long
#define vi vector<int>
#define pii pair<int,int>
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define all(x) x.begin(),x.end()
#define ull unsigned long long
#define vs vector<string>

const int INF = 1e18;
const int modx = 1e9 + 7;
const int maxn = 2e5 + 1;

struct Trie {
  struct Node {
    int ch[2] = {-1, -1};
    int c = 0;
  };
  vector<Node> nd;

  void clr() {
    nd.clear();
    nd.push_back(Node());
  }

  Trie() {
    clr();
  }

  void ins(int x) {
    int u = 0;
    nd[u].c++;
    for (int b = 29; b >= 0; b--) {
      int bit = (x >> b) & 1;
      if (nd[u].ch[bit] == -1) {
        nd[u].ch[bit] = nd.size();
        nd.push_back(Node());
      }
      u = nd[u].ch[bit];
      nd[u].c++;
    }
  }

  void del(int x) {
    int u = 0;
    nd[u].c--;
    for (int b = 29; b >= 0; b--) {
      int bit = (x >> b) & 1;
      u = nd[u].ch[bit];
      nd[u].c--;
    }
  }

  int qry(int x) {
    int u = 0;
    int res = 0;
    for (int b = 29; b >= 0; b--) {
      int bit = (x >> b) & 1;
      int w = 1 - bit;
      if (nd[u].ch[w] != -1 && nd[nd[u].ch[w]].c > 0) {
        res |= (1LL << b);
        u = nd[u].ch[w];
      } else {
        u = nd[u].ch[bit];
      }
    }
    return res;
  }

  bool emp() {
    return nd[0].c == 0;
  }
};

Trie t1, t2;

void dfs(int u, const vi &V, vi &val, vi &ans, const vector<vi> &adj) {
  for (int v : adj[u]) {
    val[v] = V[v] ^ val[u];
    ans[v] = t1.qry(val[v]);
    if (!t2.emp()) {
      ans[v] = max(ans[v], t2.qry(val[v]));
    }
    t2.ins(val[v]);
    dfs(v, V, val, ans, adj);
    t2.del(val[v]);
  }
}

void solve() {
  int n; cin >> n;

  vi A(n + 1), V(n + 1), deg(n + 1, 0);

  for (int i = 1; i <= n; i++) {
    cin >> A[i]; deg[A[i]]++;
  }
  for (int i = 1; i <= n; i++) {
    cin >> V[i];
  }

  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (!deg[i]) q.push(i);
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (--deg[A[u]] == 0) q.push(A[u]);
  }

  vector<bool> inc(n + 1, false);
  for (int i = 1; i <= n; i++) {
    if (deg[i] > 0) inc[i] = true;
  }

  vector<vi> adj(n + 1);
  for (int i = 1; i <= n; i++) {
    if (!inc[i]) adj[A[i]].push_back(i);
  }

  vi val(n + 1, 0), ans(n + 1, 0);
  vector<bool> vis(n + 1, false);
  t2.clr();

  for (int i = 1; i <= n; i++) {
    if (inc[i] && !vis[i]) {
      vi cyc;
      int cur = i;
      while (!vis[cur]) {
        vis[cur] = true;
        cyc.push_back(cur);
        cur = A[cur];
      }

      int L = cyc.size();
      vi p(L + 1, 0);
      for (int j = 0; j < L; j++) {
        p[j + 1] = p[j] ^ V[cyc[j]];
      }
      int S = p[L];

      t1.clr();
      for (int j = 0; j < L; j++) {
        t1.ins(p[j]);
        t1.ins(p[j] ^ S);
      }

      for (int j = 0; j < L; j++) {
        int c = cyc[j];
        val[c] = p[j];
        ans[c] = t1.qry(val[c]);
        dfs(c, V, val, ans, adj);
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    cout << ans[i] << (i == n ? "" : " ");
  }
  cout << "\n";
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t; cin >> t;

  while (t--) {
    solve();
  }
}