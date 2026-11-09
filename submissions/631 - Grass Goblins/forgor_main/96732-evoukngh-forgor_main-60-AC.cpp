#include<bits/stdc++.h>

using namespace std;

#define int long long
#define INF 1e18

vector<int> p;
vector<vector<int>> g;

void dfs(int u, int par) {
	p[u] = par;
	for (int v : g[u]) {
		if (v == par) continue;
		dfs(v, u);
	}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string s;
    int n;
    cin >> s >> n;
    if (s == "FIRST") {
		g = vector<vector<int>> (n);
		p = vector<int> (n, -1);
		for (int i = 1; i < n; i++) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			g[a].push_back(b);
			g[b].push_back(a);
		}
		dfs(0, 0);
		int x = 0;
		for (int i = 1; i < n; i++) {
			x = x^p[i];
			cout << p[i] << " ";
		}
		cout << x << endl;		
	} else {
		vector<int> num(n);
		for (int i = 0; i < n; i++) cin >> num[i];
		int spec = 0;
		int x = 0;
		for (int i = 0; i < n; i++) {
			if (num[i] == -1) spec = i;
			else {
				x = x^num[i];
			}
		}
		num[spec] = x;
		for (int i = 0; i < n-1; i++) {
			cout << i+2 << " " << num[i]+1 << endl;
		}
	}
}
