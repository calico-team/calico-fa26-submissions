#include<bits/stdc++.h>
using namespace std;
int T,cnt=2;
int a[10086],n,r;
int main(){
	cin>>T; 
	for(int i=1;i<=T;i++){
		cin>>n>>r;
		int flag=0; 
		for(int j=0;j<n;j++){
			cin>>a[j];
			}  
			for(int j=0;j<n;j++){
				if(floor(a[j]/r)<1){
					if(cnt>0){
						cnt--;
					}
					else flag=1;
				}
			}
			if(flag==0) cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}

	return 0;	
}
