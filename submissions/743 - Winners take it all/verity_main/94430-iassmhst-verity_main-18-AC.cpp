#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll
using P = pair<int, int>;
#define all(x) x.begin(), x.end()
#define rep(x,s,e) for (auto x=(s)-((s)>(e));x!=(e)-((s)>(e));((s)<(e)?x++:x--))
#define sz(x) (int)x.size()
const char nl = '\n';
const int N = 2e5;
const int inf = 1e9*N;

void solve() {
	int n, k; cin >> n >> k;
	vector<char> a(k);
	for (auto &i: a)cin >> i;
	
	vector<char> out(n, '_');
	for (auto i: a) {
		string s;
		rep(j, 0, n) {
			if (out[j] != '_'){s += out[j]; continue;}
			s += i;
		}
		cout << s << endl;
		string c; cin >> c;
		if (c == "CORRECT")return;
		rep(j, 0, n)out[j] = c[j];
	}
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    while (t--)solve();
    return 0;
}
