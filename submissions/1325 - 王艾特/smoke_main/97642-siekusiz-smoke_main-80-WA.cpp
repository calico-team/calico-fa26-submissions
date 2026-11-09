#include<bits/stdc++.h>
using namespace std;
#define int long long

int a[100010];

signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,r,m=2,f=1,last1=0, last2 = 0;
		cin>>n>>r;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++){
			int ti=a[i]-a[last1];
			m+=(ti/r);
			int ti2=a[i]-a[last2];
			m+=(ti2/r);
			m=min(m,2ll);
			if(m==0){
				f=0;
				break;
			}
			else{
				m--;
				if((ti/r)!=0ll||(ti2/r)==0ll){
					last2 = last1;
					last1 = i;
				}else if(last2==0ll){
					last2 = i;
				}
			}
		}
		if(f) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0; 
}



