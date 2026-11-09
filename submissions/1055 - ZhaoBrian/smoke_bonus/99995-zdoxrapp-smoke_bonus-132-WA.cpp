#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n, r, first;
		cin >> n >> r;
		vector<int> a;
		cin >> first;
		a.push_back(first);
		bool ok=true;
		for(int i=1; i<n; ++i) {
			int x;
			cin >> x;
			a.push_back(x);
			if(a[i]-a[i-1]<r)
				ok=false;
		}
		if(ok&&a.size()<=n)
			cout << "YES" << "\n";
		else
			cout << "NO" << "\n";
	}
	return 0;
}

