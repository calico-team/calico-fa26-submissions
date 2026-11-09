#include <bits/stdc++.h>
using namespace std;
struct drone{
	int x;
	int y;
	int cx = 0;
	int cy = 0;
};

int main(){
	int t;
	cin>>t;
	for(int i=0;i<t;i++){
		long long tot = 0;
		int n,k;
		cin>>n>>k;
		drone drones[100000];
		for(int j=0;j<n;j++){
			int x,y,z;
			char dir;
			cin>>x>>y>>z>>dir;
			drones[j].x=x;
			drones[j].y=y;
			if(dir=='N')drones[j].cy=1;
			if(dir=='E')drones[j].cx=1;
			
			tot+=k;
			for(int l=0;l<j;l++){
				if(drones[j].cx==drones[l].cx)continue;
				if(drones[j].cx==1){
					int sj = (drones[l].x-drones[j].x);
					int sk = (drones[j].y-drones[l].y);
					if(sj==sk && sj>0 && sj<k){
						tot-=1;
					}
				}
				else{
					int sj = (drones[l].y-drones[j].y);
					int sk = (drones[j].x-drones[l].x);
					if(sj==sk && sj>0 && sj<k){
						tot-=1;
					}
				}
			}
		}
		cout<<tot<<endl;
	}
	return 0;
}
