#include <bits/stdc++.h>
using namespace std;

struct node {
  node* children[2] = {nullptr, nullptr};
  int bit, sz;
  node (int b): bit(b), sz(0){ }
  int qry(int x) {
    if (bit == -1) return 0;
    assert(sz > 0);
    int xb = (x>>bit)&1;
    if (children[xb^1] != nullptr && children[xb^1]->sz > 0) return children[xb^1]->qry(x) | 1<<bit;
    return children[xb]->qry(x);
  }

  void change(int x, int d) {
    sz += d;
    if (bit == -1) return;
    int xb = (x>>bit)&1;
    if (children[xb] == nullptr) children[xb] = new node(bit-1);
    children[xb]->change(x, d);
  }

  ~node() {
    delete children[0];
    delete children[1];
  }
};

int main () {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> a(n), p(n);
    for (auto& x: a) cin >> x, x--;
    for (auto& x: p) cin >> x;
    vector<int> indeg(n);
    for (auto& x: a) indeg[x]++;
    vector<int> que;
    for (int i = 0; i < n; i++) {
      if (!indeg[i]) que.emplace_back(i);
    }
    for (int i = 0; i < (int)que.size(); i++) {
      int v = que[i];
      if (!--indeg[a[v]]) que.emplace_back(a[v]);
    }

    int V = n;
    vector<int> vis(n);
    for (int v: que) vis[v] = 1;
    for (int v = 0; v < n; v++) {
      if (vis[v]) continue;
      vector<int> cyc;
      for (int u = v; !vis[u]; u = a[u]) {
        cyc.emplace_back(u);
        vis[u] = 1;
      }
      int len = cyc.size();
      a[cyc.back()] = V;
      for (int i = 0; i < 2*len; i++) {
        a.emplace_back(i+1 == 2*len ? -1 : V+i+1);
        p.emplace_back(p[cyc[i % len]]);
      }
      V += 2*len;
    }
    vector<vector<int>> children(V+1);
    for (int i = 0; i < V; i++) {
      if (a[i] == -1) children[V].emplace_back(i);
      else children[a[i]].emplace_back(i);
    }

    node trie(30);
    vector<int> ans(V);
    auto dfs = [&] (auto&& self, int v, int x) -> void {
      trie.change(x, 1);
      if (v < V) {
        ans[v] = trie.qry(x);
      }
      for (int u: children[v]) {
        self(self, u, x^p[u]);
      }
      trie.change(x, -1);
    };
    dfs(dfs, V, 0);
    for (int i = 0; i < n; i++) cout << ans[i] << ' ';
    cout << '\n';
  }
}
