#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll
using P = pair<int, int>;
#define all(x) x.begin(), x.end()
#define rep(x,s,e) for (auto x=(s)-((s)>(e));x!=(e)-((s)>(e));((s)<(e)?x++:x--))
#define sz(x) (int)x.size()
const char nl = '\n';
const int inf = 1e9;
const int N = 2e5+10;
//int cnt[N];
vector<int> g[N];

void solve() {
	int n, k; cin >> n >> k;
	int out = k*n;
	vector<int> x(n), y(n), z(n);
	vector<char> d(n);
	vector<int> b;
	rep(i, 0, n) {
		cin >> x[i] >> y[i] >> z[i] >> d[i];
		//if (d[i] == 'E')b.push_back(x[i]-y[i]);
		if (d[i] == 'E') {
			g[x[i]+y[i]].push_back(y[i]);
			b.push_back(x[i]+y[i]);
		}
	}
	
	for (auto i: b) {
		sort(all(g[i]));
		vector<int>::iterator ip;
		ip = unique(all(g[i]));
		g[i].resize(distance(g[i].begin(), ip));
	}
	
	rep(i, 0, n) {
		if (d[i] == 'E')continue;
		int sum = x[i]+y[i];
		int lb = lower_bound(all(g[sum]), y[i]+1) - g[sum].begin();
		int ub = lower_bound(all(g[sum]), y[i]+k) - g[sum].begin();
		--ub;
		if (ub < lb)continue;
		out -= ub-lb+1;
	}
	cout << out << nl;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    while (t--)solve();
    return 0;
}
