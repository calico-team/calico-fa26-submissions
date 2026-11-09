#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;
const int mod = (int) (1e9 + 7);
const int _mod = 998244353;
const int inf = 1061109567;
const ll infll = 4557430888798830399;

const int N = 2e2 + 5;

int n, m, q;
char a[N][N];
int memo[N][N];
vector<vector<int>> dir;

void dfs(int i, int j) {
	if (memo[i][j]) return;
	memo[i][j] = 1;
	for (auto& d : dir) {
		int ni = i + d[0];
		int nj = j + d[1];
		if (ni < 1 || ni > n || nj < 1 || nj > m) continue;
		if ((a[i][j] == 'B' && a[ni][nj] == 'R') || (a[i][j] == 'R' && a[ni][nj] == 'B')) continue;
		dfs(ni, nj);
	}
}

void solve() {
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
		cin >> a[i][j];
		memo[i][j] = 0;
	}
	dir = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
	dfs(n, m);
	while (q--) {
		int x, y, z; cin >> x >> y >> z >> z;
		x++; y++;
		if (memo[x][y]) cout << "YES\n";
		else cout << "NO\n";
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int t = 1;
	cin >> t;
	while (t--) {
		solve();
		cout << flush;
	}
}
