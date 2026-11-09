#include<bits/stdc++.h>
#define int long long
using namespace std;
char a[1000005],b[1000005];
char c[1000005];
void solve(){
	int n,k;
	cin>>n>>k;
	for (int i=1;i<=k;i++){
		cin>>c[i];
	} 
	for (int i=1;i<=n;i++){
		a[i]=b[i]=0;
	}
	for (int i=1;i<=k;i++){
		for (int j=1;j<=n;j++){
			cout<<c[i];
		}
		cout<<endl;
		string s;cin>>s;
		if (s=="CORRECT")return;
		for (int j=1;j<=n;j++){
			b[j]=s[j-1];
			if (b[j]==c[i])a[j]=c[i];
		}
	}
	for (int i=1;i<=n;i++){
		cout<<a[i];
	}
	cout<<endl;
	string s;cin>>s;
}
signed main(){
	int t;cin>>t;
	while (t--)solve();
} 
