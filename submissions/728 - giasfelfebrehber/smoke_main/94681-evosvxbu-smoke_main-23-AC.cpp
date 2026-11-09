#include <bits/stdc++.h>
using namespace std;
#define int long long
int arr[200005];

signed main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		bool ya = true;
		int n, k;
		cin >> n >> k;
		int a = 2, b = 0;
		for(int i = 1; i <= n; i++) {
			cin >> arr[i];
		}
		for(int i = 1; i <= n; i++) {
			if(a == 2) {
				a--;
			} else {
				b += arr[i] - arr[i - 1];
				a = min(2ll, a + b / k);
				b %= k;
				if(a == 2) b = 0;
				if(a <= 0) {
					ya = false;
				} else {
					a--;
				}
			}
		}
		if(ya) {
			cout << "YES" << "\n";
		} else {
			cout << "NO" << "\n";
		}
		
	}
}

