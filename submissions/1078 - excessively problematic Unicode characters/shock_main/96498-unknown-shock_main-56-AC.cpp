#include <bits/stdc++.h>
using namespace std;
#define sq(x) (x)*(x)
int main() {
	int t;
	cin >> t;
	while(t--) {
		int n, m, q;
		cin >> n >> m >> q;
		bool trans = 0;
		if(n > m) {
			trans = 1;
			swap(n, m);
		}
		int r[q], c[q], p[q];
		for(int i=0;i<q;i++) {
			cin >> r[i] >> c[i] >> p[i];
			if(trans)
				swap(r[i], c[i]);
		}
		int ans[n][m];
		memset(ans,0,sizeof(ans));
		set<int> pts[n];
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				pts[i].insert(j);
		for(int i=q;i--;)
			for(int j=r[i]-p[i];j<=r[i]+p[i];j++) {
				while(1) {
					auto it = pts[j].lower_bound(c[i]);
					if(it == pts[j].end() || sq(*it - c[i]) + sq(j - r[i]) > sq(p[i]))
						break;
					ans[j][*it] = sq(p[i]) + 1 - sq(*it - c[i]) - sq(j - r[i]);
					pts[j].erase(it);
				}
				while(1) {
					auto it = pts[j].lower_bound(c[i]);
					if(it == pts[j].begin() || sq(*prev(it) - c[i]) + sq(j - r[i]) > sq(p[i]))
						break;
					it--;
					ans[j][*it] = sq(p[i]) + 1 - sq(*it - c[i]) - sq(j - r[i]);
					pts[j].erase(it);
				}
			}
		if(trans)
			for(int j=0;j<m;j++)
				for(int i=0;i<n;i++)
					cout << ans[i][j] << " \n"[i==n-1];
		else
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
					cout << ans[i][j] << " \n"[j==m-1];
	}
}
