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
	for(int i = 1; i <= n; i++) {
		cin >> arr[i];
	}
	for(int i = 3; i <= n; i++) {
		if((arr[i] - arr[i - 2] < k * 2)) {
			ya = false;
		}
	}
	if(ya) {
		cout << "YES" << "\n";
	} else {
		cout << "NO" << "\n";
	}
	
	}
}

