#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n, r;
		cin >> n >> r;
		if(n==1||n==2) {
			cout << "YES" << "\n";
			continue;
		}
		int a[n]={0};
		bool ok=true;
		for(int i=0; i<n; ++i) {
			cin >> a[i];
		}
		for(int i=2; i<n; ++i) {
			if(i>0&&a[i]-a[i-1]<r) {
				ok=false;
				break;
			}
		}
		if(ok) cout << "YES" << "\n";
		else cout << "NO" << "\n";
	}
	return 0;
}
