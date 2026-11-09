#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n, r;
		cin >> n >> r;
		if(n==1) {
			cout << "YES" << "\n";
			continue;
		}
		int a[n+1]={0};
		cin >> a[0];
		bool ok=true;
		for(int i=1; i<n; ++i) {
			cin >> a[i];
			if(a[i]-a[i-1]<r)
				ok=false;
		}
		if(ok)
			cout << "YES" << "\n";
		else
			cout << "NO" << "\n";
	}
	return 0;
}
