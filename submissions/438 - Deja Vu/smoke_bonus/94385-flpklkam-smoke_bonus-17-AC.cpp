#include "bits/stdc++.h"

using namespace std;

#define SZ(s) (int)s.size()

const int N = 2e5 + 5;

void slv() {

	int n, r;
	cin >> n >> r;

	vector <int> a(n+1);
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	deque <int> d;
	int cnt = 2;

	for(int i = 1; i <= n; i++) {
		while(SZ(d) and d.front() <= a[i]) {
			d.pop_front();
			cnt++;
		}
		if(cnt == 2) {
			d.push_back(a[i] + r);
			cnt--;
		}
		else if(cnt == 1) {
			d.push_back(d.front() + r);
			cnt--;
		}
		else {
			cout << "NO\n";
			return;
		}
	}

	cout << "YES\n";

	return;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);

	int T = 1;
	cin >> T;
	while(T--) slv();

	return 0;
}
