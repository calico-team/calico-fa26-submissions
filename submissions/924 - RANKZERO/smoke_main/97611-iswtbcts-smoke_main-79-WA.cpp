#include <bits/stdc++.h>
using namespace std;

 int main () {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t;
	cin>>t;
	int n,r,count,diff;
	while(t--){
		cin>>n>>r;
		count=0;
		vector<int>a(n);
		for (int i=0; i<n;i++){
			cin>>a[i];
		}
		
		for (int i=0;i<n-1;i++){
			diff=a[i+1]-a[i];
			if (diff>=r){
				count++;
			}
		}
		if (count==n-1) cout<<"YES\n"; else cout<<"NO\n";
	}
			
	return 0;
 }
