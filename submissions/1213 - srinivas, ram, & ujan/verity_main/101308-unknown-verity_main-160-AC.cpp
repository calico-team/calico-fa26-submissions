#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
	int N, K; cin >> N >> K;
	vector<char> a(K);
	for (int i = 0; i < K; i++) cin >> a[i];
	string cur(N, '_');
	int idx = 0;
	while (true) {
		string guess = cur;
		for (int i = 0; i < N; i++) {
			if (guess[i] == '_') guess[i] = a[idx];
		}
		cout << guess << endl; 
		string res; cin >> res;
		if (res == "CORRECT") break;
		for (int i = 0; i < N; i++) {
			if (res[i] != '_') cur[i] = res[i];
		}
		idx++;
	}
}

int32_t main() {
	int T; cin >> T;
	while (T--) solve();
}