#include<bits/stdc++.h>
using namespace std;
int T,cnt=2;
int a[10086],n,r;
int main(){
	cin>>T; 
	for(int i=1;i<=T;i++){
		cin>>n>>r;
		int flag=0; 
		a[0]=0;
		for(int j=1;j<=n;j++){
			cin>>a[j];
			if((a[j]-a[j-1])/r<1){
				if(cnt>=0)
				{
					cnt--;
				}
				else{
					flag = 1;
				}

			} 

		}
		if(flag == 1){
			cout<<"NO"<<endl;
		}
		else{
			cout<<"YES"<<endl;
		}
		for(int j=1;j<=n;j++)
		{
			a[j]=0;
		}
	}
	
	
	
	
	
	return 0;	
}
