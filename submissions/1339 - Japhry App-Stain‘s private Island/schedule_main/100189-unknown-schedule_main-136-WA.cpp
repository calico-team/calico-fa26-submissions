#include <bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin>>t;
	for(int i=0;i<t;i++){
		int tot = 0;
		int m,k,n;
		cin>>n>>m>>k;
		int pre[10010];
		int pred[10010];
		for(int j=0;j<n;j++){
			cin>>pre[j];
		}
		memset(pred,0,sizeof(pred));
		for(int j=0;j<m;j++){
			for(int a=0;a<k;a++){
				for(int b=0;b<n;b++){
					if(pred[b]==1)continue;
					if(pre[b]!=0 && pred[pre[b]-1]!=1)continue;
					if(pred[b]==-1)continue;
					pred[b]=-1;
					break;
				}
			}
			
			for(int b=0;b<n;b++){
				if(pred[b]==-1){
					pred[b]=1;
					//<<"done"<<b<<" ";
					tot++;
				}
			}
			//cout<<endl;
		}
		cout<<tot<<endl;
	}
	return 0;
}
