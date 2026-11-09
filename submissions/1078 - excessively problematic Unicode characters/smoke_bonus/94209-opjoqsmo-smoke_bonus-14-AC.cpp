#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int n, r;
		cin >> n >> r;
		int a[n];
		for(int i=0;i<n;i++)
			cin >> a[i];
		bool ok = 1;
		for(int i=0;i<n-2;i++)
			if(a[i+2]-a[i]<r)
				ok = 0;
		for(int i=0;i<n-3;i++)
			if(a[i+3]-a[i]<2*r)
				ok = 0;
		cout << (ok?"YES\n":"NO\n");
	}
}
