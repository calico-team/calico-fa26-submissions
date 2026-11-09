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

void solve() {
	string s; cin >> s;
	string out = "thank_you";
	int n = sz(s);
	rep(i, 0, n) {
		string c;
		rep(j, i, n) {
			c += s[j];
			if (c == "write_me")out = "make_it_sound_human";
			else if (c == "what_is")out = "do_not_hallucinate";
			else if (c == "solve")out = "make_no_mistakes";
		}
	}
	cout << s << out << nl;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    while (t--)solve();
    return 0;
}
