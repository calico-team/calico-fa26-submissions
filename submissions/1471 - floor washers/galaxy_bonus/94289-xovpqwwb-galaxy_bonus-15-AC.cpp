#include <bits//stdc++.h>
using namespace std;
#define ll long long
#define iloop(m, h) for (auto i = m; i != h; i += (m<h?1:-1))
#define jloop(m, h) for (auto j = m; j != h; j += (m<h?1:-1))
#define kloop(m, h) for (auto k = m; k != h; k += (m<h?1:-1))
#define pii pair<int, int>
#define pll pair<ll, ll>
int n, m, q;
char c;
int a[205][205];
pii par[205][205];
pii find(pii nd) {
	return (nd == par[nd.first][nd.second] ? nd : par[nd.first][nd.second] = find(par[nd.first][nd.second]));
}
void merge(pii x, pii y) {
	x = find(x), y = find(y);
	par[x.first][x.second] = y;
}
int t1, t2, t3, t4;
void solve() {
	cin >> n >> m >> q;
	iloop(0, n) jloop(0, m) {
		cin >> c;
		if (c == '.') a[i][j] = 0;
		else if (c == 'R') a[i][j] = 1;
		else a[i][j] = 2;
		par[i][j] = {i, j};
	}
	iloop(0, n) jloop(0, m) {
		if (i && (a[i][j] == 0 || a[i-1][j] == 0 || a[i][j] == a[i-1][j])) merge({i, j}, {i-1, j});
		if (j && (a[i][j] == 0 || a[i][j-1] == 0 || a[i][j] == a[i][j-1])) merge({i, j}, {i, j-1});
	}
	while (q--) {
		cin >> t1 >> t2 >> t3 >> t4;
		cout << (find({t1, t2}) == find({t3, t4}) ? "YES\n" : "NO\n");
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int q_;
	cin >> q_;
	while (q_--) solve();
}
