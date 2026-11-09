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

void solve() {
	string s; cin >> s;
	if (s.find("write_me") != string::npos) s += "make_it_sound_human";
	else if (s.find("what_is") != string::npos) s += "do_not_hallucinate";
	else if (s.find("solve") != string::npos) s += "make_no_mistakes";
	else s += "thank_you";
	cout << s << '\n';
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
