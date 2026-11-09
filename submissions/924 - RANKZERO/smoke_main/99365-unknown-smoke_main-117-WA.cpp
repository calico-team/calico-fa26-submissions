#include <bits/stdc++.h>
using namespace std;

 int main () {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t;
	cin>>t;
	int n,r,count,diff;
	bool cool=true;
	while(t--){
		cin>>n>>r;
		count=0;
		vector<int>a(n);
		for (int i=0; i<n;i++){
			cin>>a[i];
		}
		
		for (int i=0;i<n-2;i++){
			if ((a[i+1]-a[i])>=r){
				continue;
			} else if ((a[i+2]-a[i])>=r){
				continue;
			} else {
				cout<<"NO\n";
				break;
			}
		}
		if (cool) cout<<"YES\n";
		
	}
			
	return 0;
 }
