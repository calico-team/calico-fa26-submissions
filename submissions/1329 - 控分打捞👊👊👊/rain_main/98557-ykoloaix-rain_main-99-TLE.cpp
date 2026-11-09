#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin>>n;
	for(int in=0;in<n;in++){
		int n,k;
		long long ans=0;
		char j1;
		vector<int> x(n+10,0),y(n+10,0),z(n+10,0);
		vector<bool> dir(n+10,0); 
		cin>>n>>k;
		for(int i=0;i<n;i++){
			cin>>x[i]>>y[i]>>z[i]>>j1;
			if(j1=='E')dir[i]=1;
			else dir[i]=0;
		}
		for(int i=0;i<k;i++){
			for(int j=0;j<n;j++){
				bool b=1;
				for(int ii=0;ii<n;ii++){
					if(x[j]==x[ii]&&y[j]==y[ii]&&z[j]<z[ii])b=0;
				}
				if(b){
					//cout<<x[j]<<y[j]<<z[j]<<endl;
					ans++;
				}
			}
			for(int j=0;j<n;j++){
				if(dir[j]==1)x[j]++;
				else y[j]++;
			}
			
		}
		cout<<ans<<endl;
	}
	return 0;
}
