#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n, r, first, second;
		cin >> n >> r;
		int a[n]={0};
		bool ok=true;
		for(int i=0; i<n; ++i) {
			cin >> a[i];
		}
		for(int i=0; i<n; ++i) {
			if(first<=a[i]) {
				first=r+max(a[i], second);
			}
			else if(second<=a[i]) {
				second=r+max(a[i], first);
			}
			else {
				ok=false;
				break;
			}
		}
		if(ok) cout << "YES" << "\n";
		else cout << "NO" << "\n";
	}
	return 0;
}
