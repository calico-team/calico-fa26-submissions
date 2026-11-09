
#include <bits/stdc++.h>
using namespace std;

int a[202005];

long long pref[202005];

int main() {
	int t;
	cin>>t;
	while(t--) {
		int n, r;
		cin>>n>>r;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) pref[i] = 1LL * (a[i] - a[i-1]);
		int charge = 2;
		long long diff = 0;
		bool smoke = true;
		for(int i=1;i<=n;i++) {
			diff += pref[i];
			int sum = diff/(long long)(r);
			diff %= r;
			charge = min(charge + sum, 2);
			if(charge == 2) diff = 0;
			if(charge == 0) {
				smoke = false;
				break;
			}
			charge--;
		}
		if(smoke) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
}
