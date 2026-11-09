
#include <bits/stdc++.h>

using namespace std;

void solve() {
    long long n, r;
    cin >> n >> r;
    vector<long long> a(n);
    for (long long &x : a) cin >> x;

    for (int i = 2; i < n; ++i) {
    	if ((a[i] - a[i - 1]) < r) {
		cout << "NO\n";
		return;
	}
    }

    cout << "YES" << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
