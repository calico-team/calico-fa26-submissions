#include <bits//stdc++.h>
using namespace std;
#define ll long long
#define iloop(m, h) for (auto i = m; i != h; i += (m<h?1:-1))
#define jloop(m, h) for (auto j = m; j != h; j += (m<h?1:-1))
#define kloop(m, h) for (auto k = m; k != h; k += (m<h?1:-1))
#define pii pair<int, int>
#define pll pair<ll, ll>
string s;
int n;
vector<int> adj[200005];
int a[200005], par[200005];
int u, v;
int ts, ts2;
void dfs(int nd, int pr) {
	par[nd] = pr;
	if (pr != -1) ts += nd + pr;
	for (auto it : adj[nd]) if (it != pr) dfs(it, nd);
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> s;
	if (s == "FIRST") {
		cin >> n;
		iloop(1, n) {
			cin >> u >> v;
			adj[u-1].push_back(v-1);
			adj[v-1].push_back(u-1);
		}
		ts = 0;
		dfs(0, -1);
		ts2 = ts;
		//cout << ts2 << ",";
		iloop(1, n) {
			cout << par[i] + (ts2%5)*200000 << " ";
			ts2 /= 5;
		}
		cout << ts%200000;
		return 0;
	}
	cin >> n;
	iloop(0, n) cin >> a[i];
	ts = 0;
	if (a[n-1] == -1) {
		iloop(0, n-1) cout << i+2 << " " << (a[i]%200000)+1 << "\n";
		return 0;
	}
	int sp = -1, ep = -1;
	iloop(0, n-1) {
		if (a[i] != -1) {
			cout << i+2 << " " << (a[i]%200000)+1 << "\n";
			ts += i+1 + (a[i]%200000);
		}
		else sp = i, ts += i+1;
	}
	ts %= 200000;
	//cout << ts << "," << a[n-1] << "\n";
	ep = (a[n-1] + 400000 - ts)%200000;
	cout << sp + 2 << " " << ep + 1;
}
