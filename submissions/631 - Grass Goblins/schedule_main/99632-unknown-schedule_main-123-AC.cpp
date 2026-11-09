#include<bits/stdc++.h>

using namespace std;

#define int long long
#define INF 1e18

int n, m, k;
vector<vector<int>> g;
vector<int> dp;
vector<int> anz;

void dfs(int u, int l) {
	if (l == m) return;
	anz[l]++;
	//~ vector<int> add;
	for (int v : g[u]) {
		dfs(v, l+1);
		//~ add.push_back(dp[v]+1);
	}
}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
		cin >> n >> m >> k;
		g = vector<vector<int>> (n+1);
		//~ dp = vector<int> (n+1, 0);
		anz = vector<int> (m, 0);
		for (int i = 1; i <= n; i++) {
			int p;
			cin >> p;
			g[p].push_back(i);
		}
		for (int u : g[0]) {
			dfs(u, 0);
		}
		int spare = 0;
		int ans = 0;
		for (int l = m-1; l >= 0; l--) {
			spare += k;
			ans += min(spare, anz[l]);
			spare -= min(spare, anz[l]);
		}
		cout << ans << endl;
	}
}
