#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie();

	string phase;
	int n;
	cin >> phase >> n;

	const int MOD = 1000000;

	if (phase == "FIRST") {
		vector<vector<int> > g(n + 1);

		for (int i = 0; i < n - 1; i++) {
			int u, v;
			cin >> u >> v;

			g[u].push_back(v);
			g[v].push_back(u);
		}

		vector<int> parent(n + 1, 0);
		vector<int> order;
		order.push_back(1);
		parent[1] = -1;

		for (int i = 0; i < (int)order.size(); i++) {
			int u = order[i];

			for (int j = 0; j < (int)g[u].size(); j++) {
				int v = g[u][j];
				if (v == parent[u]) {
					continue;
				}
				parent[v] = u;
				order.push_back(v);
			}
		}

		long long sum = 0;
		for (int i = 2; i <= n; i++) {
			cout << parent[i] << ' ';
			sum += parent[i];
		}
		cout << sum % MOD << '\n';

	} else {

		vector<int> a(n);

		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}

		long long sum = 0;
		int missing = -1;

		for (int i = 0; i < n - 1; i++) {
			if (a[i] == -1) {
				missing = i;
			} else {
				sum += a[i];
			}
		}

		if (missing != -1) {
			a[missing]=(a[n - 1] - sum % MOD + MOD) % MOD;
		}

		for (int i = 2; i <= n; i++) {
			cout << i << ' ' << a[i - 2] << '\n';
		}
	}

	return 0;
}
