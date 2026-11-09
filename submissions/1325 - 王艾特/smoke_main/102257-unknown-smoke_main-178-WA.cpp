#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,r,m=2,f=1,last=0,last2=1e18;
		cin>>n>>r;
		for(int i=1;i<=n;i++){
			int x;
			cin>>x;
			int ti=x-last2;
			if(ti>=r){
				m+=ti/r;
				last2=x-(ti%r);
				if(m>2) m=2;
			}
			if(m==0) f=0;
			else m--,last2=min(last2,x);
		}
		if(f) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0; 
}
