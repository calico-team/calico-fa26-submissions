#include<bits/stdc++.h>
using namespace std;
int T,n,r,sum=2,flag=0;
int a[100005]; 
int main(){
	cin>>T;
	while(T--){
		cin>>n>>r;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		a[n+1] = 0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]-a[i-1]>=r && i!=1 && sum<2) sum+=(a[i]-a[i-1])/r;
			if (sum>2) sum = 2;	
			sum--;
			if(sum<0){
				cout<<"NO"<<endl;
				flag=1;
				break;
			} 
		}
		if(!flag) cout<<"YES"<<endl;
		flag = 0;
		sum = 2;
	}
	return 0;
}
