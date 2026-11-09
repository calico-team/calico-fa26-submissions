#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<algorithm>
#include <iterator>
#include <vector>
#include<utility>
#include<cmath>
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
vector<vector<int>> fwd;
int fnd(int i,int j) {
	int mov=j;
	while (fwd[i][mov]!=mov) {
		mov=fwd[i][mov];
	}
	while (fwd[i][j]!=mov) {
		int nxt = fwd[i][j];
		fwd[i][j]=mov;
		j=nxt;
	}
	return mov;
}
int main() {
	// setIO("berries");
	ll t;
	cin>>t;
	while (t--) {
		ll n,m,q;
		cin>>n>>m>>q;
		vector<ll> R(q),C(q),P(q);
		fwd=vector<vector<int>>(n,vector<int>(m+1,0));
		vector<vector<int>>ans (n,vector<int>(m+1,0));
		for (int i=0;i<n;i++) {
			for (int j=0;j<=m;j++) {
				fwd[i][j]=j;
			}
		}
		for (int i=0;i<q;i++) {
			cin>>R[i]>>C[i]>>P[i];
		}
		reverse(R.begin(), R.end());
		reverse(C.begin(), C.end());
		reverse(P.begin(), P.end());
		for (int s=0;s<q;s++) {
			for (int i=R[s]-P[s];i<=min(n,R[s]+P[s]);i++) {
				ll d = P[s]*P[s]-(R[s]-i)*(R[s]-i);
				if (d < 0) {
					continue;
				}
				int w = int(floor(sqrt(d)));
				int left = max(0LL,C[s]-w),right=min(m-1,C[s]+w);

				for (int j=fnd(i,left);j<=right;j=fnd(i,j+1)) {
					ans[i][j]=s;
					fwd[i][j]=j+1;
				}
			}
		}
		for (int i=0;i<n;i++) {
			for (int j=0;j<m;j++) {
				cout<<max(P[ans[i][j]]*P[ans[i][j]]-((R[ans[i][j]]-i)*(R[ans[i][j]]-i)+(C[ans[i][j]]-j)*(C[ans[i][j]]-j))+1,0LL)<<" ";
			}
			cout<<'\n';
		}
	}
	return 0;
}
