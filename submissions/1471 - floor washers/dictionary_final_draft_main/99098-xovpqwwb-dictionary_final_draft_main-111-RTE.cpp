#include <bits//stdc++.h>
using namespace std;
#define ll long long
#define iloop(m, h) for (auto i = m; i != h; i += (m<h?1:-1))
#define jloop(m, h) for (auto j = m; j != h; j += (m<h?1:-1))
#define kloop(m, h) for (auto k = m; k != h; k += (m<h?1:-1))
#define pii pair<int, int>
#define pll pair<ll, ll>
int n;
int a[200005], b[200005];
vector<int> adj[200005];
vector<vector<int>> cs;
int vis[200005];
bool cyc[200005];
int dfs(int nd) {
	vis[nd] = 1;
	int tail = -1;
	for (auto it : adj[nd]) {
		if (vis[it] == 2) continue;
		if (vis[it] == 1) {
			cyc[nd] = 1;
			cs.push_back({nd});
			tail = it;
			continue;
		}
		int tmp = dfs(it);
		if (tmp != -1) {
			cyc[nd] = 1;
			cs.back().push_back(nd);
			if (tmp == nd) tmp = -1;
			tail = tmp;
		}
	}
	vis[nd] = 2;
	return tail;
}
struct trie {
	int dpt;
	int f;
	trie *l, *r;
	trie (int dp) {
		dpt = dp;
		f = 0;
		l = r = nullptr;
	}
	void add(int k) {
		f++;
		if (dpt == 30) {return;}
		if (k&(1<<(29 - dpt))) {
			if (r == nullptr) r = new trie(dpt + 1);
			r->add(k);
			return;
		}
		if (l == nullptr) l = new trie(dpt + 1);
		l->add(k);
	}
	void rem(int k) {
		f--;
		if (dpt == 30) {return;}
		if (k&(1<<(29 - dpt))) {
			if (r == nullptr) r = new trie(dpt + 1);
			r->rem(k);
			return;
		}
		if (l == nullptr) l = new trie(dpt + 1);
		l->rem(k);
	}
	int find(int k) {
		if (dpt == 30) return 0;
		if (k&(1<<(29 - dpt))) {
			if (l == nullptr || l->f == 0) return r->find(k);
			else return (1<<(29 - dpt)) + l->find(k);
		}
		if (r == nullptr || r->f == 0) return l->find(k);
		else return (1<<(29 - dpt)) + r->find(k);
	}
} *root, *root2;
int ans[200005];
int cx, cv, cy;
void dfs3(int nd) {
	root2->add(cy);
	cy ^= a[nd];
	ans[nd] = max(root->find(cx^cy), root2->find(cy));
	for (auto it : adj[nd]) if (!cyc[it]) dfs3(it);
	cy ^= a[nd];
	root2->rem(cy);
}
void solve() {
	cin >> n;
	iloop(0, n) adj[i].clear();
	iloop(0, n) {
		cin >> b[i];
		b[i]--;
		adj[b[i]].push_back(i);
	}
	iloop(0, n) cin >> a[i];
	memset(vis, 0, sizeof(vis));
	cs.clear();
	memset(cyc, 0, sizeof(cyc));
	iloop(0, n) if (!vis[i]) dfs(i);
	for (auto it : cs) {
		cx = 0, cv = 0;
		root = new trie(0);
		for (auto it2 : it) {
			cv ^= a[it2];
			root->add(cv);
		}
		for (auto it2 : it) {
			cv ^= a[it2];
			root->add(cv);
		}
		for (auto it2 : it) {
			root2 = new trie(0);
			root2->add(0);
			cy = 0;
			cx ^= a[it2];
			dfs3(it2);
		}
	}
	iloop(0, n) cout << ans[i] << " ";
	cout << "\n";
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int q_;
	cin >> q_;
	while (q_--) solve();
}
