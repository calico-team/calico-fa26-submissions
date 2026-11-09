#include "bits/stdc++.h"

using namespace std;

#define SZ(s) (int)s.size()
#define ll long long

const int N = 2e5 + 5;

vector <int> v[N];

int ind[N];

void slv() {

	ll n, k;
	cin >> n >> k;

	ll ans = (n * k);
	vector <int> x(n+1), y(n+1), z(n+1), d(n+1);
	vector <pair <int, int>> v1;
	map <int, int> mp;
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		char c;
		cin >> x[i] >> y[i] >> z[i] >> c;
		if(c == 'E') d[i] = 0;
		else d[i] = 1;
		if(d[i]) v[x[i] + y[i]].push_back(x[i]);
		else v1.push_back({x[i], y[i]});
	}
	sort(v1.rbegin(), v1.rend());
	for(int i = 1; i <= n; i++) {
		int in = x[i] + y[i];
		sort(v[in].rbegin(), v[in].rend());
		ind[in] = SZ(v[in]);
	}

	while(SZ(v1)) {
		auto [a, b] = v1.back();
		v1.pop_back();
		int in = a + b;
		while(SZ(v[in]) and v[in].back() < a) {
			v[in].pop_back();
		}
		ind[in] = min(ind[in], SZ(v[in]));
		while(ind[in] and (v[in][ind[in]-1] - a) < k) {
			ind[in]--;
		}
		ans -= (SZ(v[in]) - ind[in]);
	}

	cout << ans << '\n';

	for(int i = 1; i <= n; i++) {
		v[x[i] + y[i]].clear();
	}

	return;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);

	int T = 1;
	cin >> T;
	while(T--) slv();

	return 0;
}
