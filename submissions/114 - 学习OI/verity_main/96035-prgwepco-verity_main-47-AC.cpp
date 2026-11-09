#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 110;
ll n, k, pos[N]; char alph[N];
void solve()
{
	cin >> n >> k;
	for (ll i = 1; i <= k; i++) cin >> alph[i];
	for (ll i = 0; i < n; i++) pos[i] = 1;
	for (ll step = 1; ; step++)
	{
		string s = "";
		for (ll j = 0; j < n; j++) s += alph[pos[j]];
		cout << s << '\n', cout.flush();
		string tmp; cin >> tmp;
		if (tmp == "CORRECT") return ;
		for (ll j = 0; j < n; j++)
			if (tmp[j] == '_') pos[j]++;
	}
}

int main()
{
	ll T = 1; cin >> T;
	while (T--) solve();
	return 0;
}
