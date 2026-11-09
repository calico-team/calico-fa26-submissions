#include<bits/stdc++.h>
using namespace std;
#define int long long

int a[100010];

signed main(){
	string s;
	int t;
	cin>>t;
	while(t--){
		int n,r,m=2,f=1,last=0;
		cin>>n>>r;
		for(int i=1;i<=n;i++){
			int x;
			cin>>x;
			int ti=x-last;
			m+=(ti/r);
			m=min(m,2ll);
			if(m==0){
				f=0;
				break;
			}
			else m--;
			last=x;
		}
		if(f) cout<<"YES\n";
		else cout<<"NO\n";
	}
}
