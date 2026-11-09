#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, m, k;
	cin >> n >> m >> k;
	bool S = n > m;
	if (S) swap(n, m);
	int st[n][m][20], X[k], Y[k], R[k];
	memset(st, 0, sizeof st);
	for (int i = 0; i < k; i++) {
		cin >> X[i] >> Y[i] >> R[i];
		if (S) swap(X[i], Y[i]);
		for (int x = max(0, X[i] - R[i]); x < n && x <= X[i] + R[i]; x++) {
			int dy = sqrtf(R[i] * R[i] - (x - X[i]) * (x - X[i]));
			for (int y = Y[i] - dy, b = 19; b >= 0; b--) {
				if ((Y[i] + dy + 1) - y >= 1 << b) {
					if (y < m) st[x][y][b] = i;
					y += 1 << b;
				}
			}
		}
	}
	#pragma GCC ivdep
	for (int i = 0; i < n; i++) {
		for (int b = 19; b; b--) {
			for (int j = 0; j < m; j++) {
				st[i][j][b - 1] = max(st[i][j][b - 1], st[i][j][b]);
				if (j + (1 << b - 1) < m) st[i][j + (1 << b - 1)][b - 1] = max(st[i][j + (1 << b - 1)][b - 1], st[i][j][b]);
			}
		}
	}
	if (S) for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			int k = st[i][j][0];
			cout << max(0, R[k] * R[k] - (i - X[k]) * (i - X[k]) - (j - Y[k]) * (j - Y[k]) + 1) << ' ';
		}
		cout << '\n';
	}
	else for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int k = st[i][j][0];
			cout << max(0, R[k] * R[k] - (i - X[k]) * (i - X[k]) - (j - Y[k]) * (j - Y[k]) + 1) << ' ';
		}
		cout << '\n';
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t--) solve();
}