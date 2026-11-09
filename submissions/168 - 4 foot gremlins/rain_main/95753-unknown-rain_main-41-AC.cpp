#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<algorithm>
#include <iterator>
#include <vector>
#include<utility>
#include<queue>
#include<map>
#include<set>
using ll = long long;
using pii=std::pair<ll,ll>;
using pll=std::pair<ll,ll>;
using namespace std;
void setIO(const string& s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
vector<ll> ebuckets[ll(2e5)],nbuckets[ll(2e5)];
int main() {
	// setIO("berries");
	ll t;
	cin>>t;
	while (t--) {
		ll n,k;
		cin>>n>>k;
		ll xi[n],yi[n],zi[n];char di[n];
		for (ll i=0;i<n;i++) {
			cin>>xi[i]>>yi[i]>>zi[i]>>di[i];
		}
		for (ll i=0;i<n;i++) {
			if (di[i]=='E') {
				ebuckets[xi[i]+yi[i]].push_back(xi[i]);
			}else {
				nbuckets[xi[i]+yi[i]].push_back(xi[i]);
			}
		}
		ll tot=0;
		for (ll j=0;j<ll(2e5);j++) {
			sort(ebuckets[j].begin(),ebuckets[j].end());
			sort(nbuckets[j].begin(),nbuckets[j].end());
			for (ll l:ebuckets[j]) {
				ll id1=lower_bound(nbuckets[j].begin(),nbuckets[j].end(),l)-nbuckets[j].begin();
				ll id2=upper_bound(nbuckets[j].begin(),nbuckets[j].end(),l+k-1)-nbuckets[j].begin();
				tot+=id2-id1;
			}
		}
		cout<<n*k-tot<<'\n';
		for (ll i = 0; i < n; i++) {
			ebuckets[xi[i] + yi[i]].clear();
			nbuckets[xi[i] + yi[i]].clear();
		}
	}
	return 0;
}
