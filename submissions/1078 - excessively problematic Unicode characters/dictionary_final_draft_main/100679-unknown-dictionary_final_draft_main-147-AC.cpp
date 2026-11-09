#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
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

		vector<pair<int,int>> tchild = {{-1,-1}};
		vector<int> tcnt = {0};
		auto add = [&tchild,&tcnt](int x, int w) {
			int cur = 0;
			for(int i=30;i--;) {
				int bit = !!(x&(1<<i));
				if(bit) {
					if(tchild[cur].second == -1) {
						tchild[cur].second = tchild.size();
						tcnt.push_back(0);
						tchild.push_back({-1,-1});
					}
					cur = tchild[cur].second;
					tcnt[cur]+=w;
				} else {
					if(tchild[cur].first == -1) {
						tchild[cur].first = tchild.size();
						tcnt.push_back(0);
						tchild.push_back({-1,-1});
					}
					cur = tchild[cur].first;
					tcnt[cur]+=w;
				}
			}
		};
		auto getxor = [&tchild,&tcnt](int x) {
			int ans = 0;
			int cur = 0;
			for(int i=30;i--;) {
				int bit = !!(x&(1<<i));
				if(bit) {
					if(tchild[cur].first != -1 && tcnt[tchild[cur].first]) {
						ans |= (1 << i);
						cur = tchild[cur].first;
					} else
						cur = tchild[cur].second;
				} else {
					if(tchild[cur].second != -1 && tcnt[tchild[cur].second]) {
						ans |= (1 << i);
						cur = tchild[cur].second;
					} else
						cur = tchild[cur].first;
				}
			}
			return ans;
		};

		auto dfs = [&child,&vis,&v,&add,&getxor,&ans](auto &dfs, int x, int cur) -> void {
			vis[x]++;
			add(cur,1);
			ans[x] = max(ans[x], getxor(cur));
			for(auto i: child[x])
				if(vis[i] < 3)
					dfs(dfs, i, cur^v[i]);
			add(cur,-1);
		};

		for(int i=0;i<n;i++)
			if(vis[i] == 0) {
				int h=i, t=i;
				do {
					h = a[a[h]];
					t = a[t];
				} while(h != t);
				dfs(dfs, h, v[h]);
			}
		for(int i=0;i<n;i++)
			cout << ans[i] << " \n"[i==n-1];
	}
}

