#include<bits/stdc++.h>
using namespace std;
#define int long long

int a[100010];

signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,r,m=1,f=1;
		cin>>n>>r;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=2;i<=n;i++){
			int ti=a[i]-a[i-1];
			m+=(ti/r);
			m=min(m,2ll);
			if(m==0){
				f=0;
				break;
			}
			else m--;
		}
		if(f) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0; 
}
