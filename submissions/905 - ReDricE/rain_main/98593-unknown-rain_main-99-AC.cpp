#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, k;
vector<int> E[200005], N[200005];

void solve(){
	for(int i=0; i<=200000; i++){
		E[i].clear();
		N[i].clear();
	}
	scanf("%lld %lld", &n, &k);
	for(int i=0; i<n; i++){
		int x, y, z;
		char d;
		scanf("%d %d %d %c", &x, &y, &z, &d);
		if(d == 'E') E[x+y].push_back(x);
		else N[x+y].push_back(x);
	}
	ll res = n*k;
	for(int i=0; i<=200000; i++){
		sort(N[i].begin(), N[i].end());
		for(int x : E[i]){
			auto l = upper_bound(N[i].begin(), N[i].end(), x);
			auto r = upper_bound(N[i].begin(), N[i].end(), x+k-1);
			res -= r-l;
		}
	}
	printf("%lld\n", res);
}

int main(){
	int t = 1;
	scanf("%d", &t);
	while(t--) solve();
}