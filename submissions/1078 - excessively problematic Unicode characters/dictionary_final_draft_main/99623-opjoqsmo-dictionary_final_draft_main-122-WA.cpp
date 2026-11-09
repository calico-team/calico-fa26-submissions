#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
const int FIXED_RANDOM = 0x1434670;
int main() {
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		vector<int> a(n), v(n);
		vector<vector<int>> child(n);
		vector<int> vis(n,0);
		vector<int> ans(n,0);
		for(int i=0;i<n;i++) {
			cin >> a[i];
			child[--a[i]].push_back(i);
		}
		for(int i=0;i<n;i++)
			cin >> v[i];
		unordered_map<int,int> seg;
		for(int i=(1<<30)|FIXED_RANDOM;i>1;i>>=1)
			seg[i]=1;
		auto dfs = [&seg,&child,&vis,&v,&ans](auto &dfs, int x, int cur) -> void {
			vis[x]++;
			int val = 1;
			int curans = 0;
			for(int i=30;i--;) {
				int bit = !!(cur&(1<<i));
				if(seg[(val<<1)|(bit^1)]) {
					curans |= (1<<i);
					val = (val<<1)|(bit^1);
				} else
					val = (val<<1)|bit;
			}
			ans[x] = max(ans[x], curans);
			for(int i=(1<<30)|cur;i>1;i>>=1)
				seg[i]++;
			for(auto i: child[x])
				if(vis[i] < 2)
					dfs(dfs, i, cur^v[i]);
			for(int i=(1<<30)|cur;i>1;i>>=1)
				seg[i]--;
		};
		for(int i=0;i<n;i++)
			if(vis[i] == 0) {
				int h=i, t=i;
				do {
					h = a[a[h]];
					t = a[t];
				} while(h != t);
				int x=0;
				do {
					x ^= v[h];
					h = a[h];
				} while(h != t);
				for(int j=(1<<30)|(x^FIXED_RANDOM);j>1;j>>=1)
					seg[j]++;
				dfs(dfs, h, v[h]^FIXED_RANDOM);
				for(int j=(1<<30)|(x^FIXED_RANDOM);j>1;j>>=1)
					seg[j]--;
			}
		for(int i=0;i<n;i++)
			cout << ans[i] << " \n"[i==n-1];
	}
}
