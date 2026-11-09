#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> adj[200005];
int dep[200005], depa[200005];

void dfs(int a) {
	for(int i = 0; i < adj[a].size(); i++) {
		int b = adj[a][i];
		dep[b] = dep[a] + 1;
		depa[dep[b]]++;
		dfs(b);
	}
}

signed main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int n, m, k;
		cin >> n >> m >> k;
		for(int i = 1; i <= n; i++) {
			int a;
			cin >> a;
			adj[a].push_back(i);
		}
		dfs(0);
		int tot = 0;
		for(int i = 1; i <= min(m, n); i++) {
			if(depa[i] > k) {
				tot += k;
				depa[i + 1] += depa[i] - k;
			} else {
				tot += depa[i];
			}
		}
		cout << tot << "\n";
		for(int i = 0; i <= n + 1; i++) {
			adj[i].clear();
			dep[i] = 0;
			depa[i] = 0;
		}
	}
	
}

