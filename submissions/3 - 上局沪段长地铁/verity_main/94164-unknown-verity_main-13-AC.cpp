#include<bits/stdc++.h>
using namespace std;
#define ll long long
char jky[50];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll T;
	cin>>T;
	while(T--){
		ll n,k;
		cin>>n>>k;
		for(ll i=1;i<=k;i++)cin>>jky[i];
		string s="";
		for(ll i=1;i<=n;i++)s+=jky[1];
		cout<<s<<endl;
		string rcv="";
		ll jl=2;
		while(cin>>rcv){
			if(rcv=="CORRECT")break;
			s=rcv;
			for(ll i=0;i<n;i++)if(s[i]=='_')s[i]=jky[jl];
			jl++;
			cout<<s<<endl;
		}
	}
	return 0;
}
