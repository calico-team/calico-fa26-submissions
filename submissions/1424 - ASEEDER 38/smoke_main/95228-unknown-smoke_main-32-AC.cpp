#include<bits/stdc++.h>
//#define int long long
using namespace std;
int n,k,a[1000005];
void solve(){
	cin>>n>>k;
	for (int i=1;i<=n;i++){
		cin>>a[i];
	}
	int p=2,nxt=1e9;
	for (int i=1;i<=n;i++){
		nxt-=(a[i]-a[i-1]);
		while (p<2&&nxt<=0){
			nxt+=k,p++;
		}
		if (p==2)nxt=k;
		if (p==0){
			cout<<"NO\n";
			return;
		}
		p--;
		//cout<<i<<" "<<p<<" "<<nxt<<"\n";
	}
	cout<<"YES\n";
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;cin>>t;
	while (t--)solve();
} 
