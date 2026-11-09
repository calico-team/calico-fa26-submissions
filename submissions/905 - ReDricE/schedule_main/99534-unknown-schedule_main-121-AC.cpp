#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m, k;
int d[10004];
int p[10004];
int dd[50004];
vector<int> vtx[10004];
int cnt[10004];

void solve(){
	scanf("%d %d %d", &n, &m, &k);
	for(int i=1; i<=n; i++){
		scanf("%d", &p[i]);
		vtx[p[i]].push_back(i);
		if(p[i]) cnt[i] = 1;
	}
	queue<int> q;
	for(int i=1; i<=n; i++){
		if(!cnt[i]) q.push(i);
	}
	while(!q.empty()){
		auto cur = q.front(); q.pop();
		for(auto nxt : vtx[cur]){
			d[nxt] = d[cur]+1;
			q.push(nxt);
		}
	}
	for(int i=1; i<=n; i++){
		dd[d[i]]++;
	}
	int res = 0;
	int cur = 0;
	for(int i=0; i<m; i++){
		cur += dd[i];
		res += min(k, cur);
		cur -= min(k, cur);
	}
	printf("%d\n", res);
	for(int i=0; i<=n; i++){
		d[i] = 0;
		dd[i] = 0;
		vtx[i].clear();
		cnt[i] = 0;
	}
}

int main(){
	int t = 1;
	scanf("%d", &t);
	while(t--) solve();
}