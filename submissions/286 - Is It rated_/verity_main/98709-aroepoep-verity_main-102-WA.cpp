
#include <bits/stdc++.h>
using namespace std;

char a[27];

int main() {
	int t;
	cin>>t;
	while(t--) {
		int n, k;
		cin>>n>>k;
		for(int i=0;i<k;i++) cin>>a[i];
		vector <char> cor(n + 1);
		string res;
		for(int i=0;i<k;i++) {
			for(int j=0;j<n;j++) cout<<a[i];
			cout<<endl;
			cin>>res;
			res = " " + res;
			for(int j=1;j<=n;j++) if(res[j] != '_') cor[j] = a[i];
		}
		for(int i=1;i<=n;i++) cout<<cor[i]<<endl;
	}
}
