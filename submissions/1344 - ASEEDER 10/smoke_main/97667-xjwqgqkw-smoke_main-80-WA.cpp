#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	/*int d[t];
	for(int i=0;i<t;i++){
		d[i]=0;
	} */
	for(int i=0;i<t;i++){
		int n,r;
		cin>>n>>r;
		int a[n-1];
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
			//d[i]=1;
			cout<<"NO"<<endl;
		}
		else{
			//d[i]=0;
			cout<<"YES"<<endl;
		}
	}
	/*for(int i=0;i<t;i++){
		if(d[i]==0){
			
		}
		else{
			
		} 
	}*/
}
