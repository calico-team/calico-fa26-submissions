#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	for(int i=0;i<t;i++){
		int n,r;
		cin>>n>>r;
		int a[n];
		for(int j=0;j<n;j++){
			cin>>a[j];
		}
		int f=1;
		for(int j=0;j<n-1;j++){
			if(a[j]+r<=a[j+1]){
				f++;
				
			}
		}
		if(f!=n){
			cout<<"NO"<<endl;
		}
		else{
			cout<<"YES"<<endl;
		}
	}
}
