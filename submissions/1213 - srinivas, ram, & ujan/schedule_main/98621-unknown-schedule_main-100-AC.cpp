#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 10005;
vector<int> ch[MAXN];
int depth[MAXN];

int dfs(int u) {
	depth[u] = 1;
	for (auto v : ch[u]) depth[u] = max(depth[u], dfs(v) + 1);
	return depth[u];
}

void solve() {
	int N, M, K; cin >> N >> M >> K;
	for (int i = 0; i <= N; i++) ch[i].clear();
	for (int i = 1; i <= N; i++) {
		int p; cin >> p;
		ch[p].push_back(i);
	}
	for (auto u : ch[0]) dfs(u);
	priority_queue<pair<int, int>> pq;
	for (auto u : ch[0]) pq.push({depth[u], u});
	int ans = 0;
	for (int sem = 0; sem < M && !pq.empty(); sem++) {
		vector<int> taken;
		while (taken.size() < K && !pq.empty()) {
			taken.push_back(pq.top().second);
			pq.pop();
		}
		ans += taken.size();
		for (auto u : taken) {
			for (auto v : ch[u]) pq.push({depth[v], v});
		}
	}
	cout << ans << "\n";
}

int32_t main() {
	int T; cin >> T;
	while (T--) solve();
}