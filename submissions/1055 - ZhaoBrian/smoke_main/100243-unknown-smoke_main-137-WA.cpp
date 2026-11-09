#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n, r;
		cin >> n >> r;
		vector<int> a;
		bool ok=true;
		for(int i=0; i<n; ++i) {
			int x;
			cin >> x;
			a.push_back(x);
		}
		for(int i=1; i<n; ++i) {
			if(i>0&&a[i]-a[i-1]<r)
				ok=false;
		}  
		if(ok)
			cout << "YES" << "\n";
		else
			cout << "NO" << "\n";
	}
	return 0;
}

