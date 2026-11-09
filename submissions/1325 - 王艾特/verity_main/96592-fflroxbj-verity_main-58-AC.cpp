#include<bits/stdc++.h>
using namespace std;
#define int long long

char a[100010];

signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=m;i++){
			cin>>a[i];
		}
		string s="";
		for(int i=1;i<=n;i++) s+="_";
		for(int i=1;i<=m;i++){
			for(int j=0;j<n;j++) if(s[j]=='_') s[j]=a[i];
			cout<<s<<endl;
			string x;
			cin>>x;
			if(x=="CORRECT") break;
			else s=x;
		}
	}
	return 0; 
}
