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
		int x,y;
		x=0;
		y=0; 
		for(int j=0;j<n-1;j++){
			if(a[j]>=x){
				f++;
				//x=x-r;
			}
			else{
				if(a[j]>=y){
					f++;
					//y=y-r;
				}
			}
			x+=r;
			y+=r;
		}
		if(f!=n){
			cout<<"NO"<<endl;
		}
		else{
			cout<<"YES"<<endl;
		}
	}
}
