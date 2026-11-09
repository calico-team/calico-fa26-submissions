#include<bits/stdc++.h>
using namespace std;
#define int long long

int a[200010];
struct dr{
	int x,y;
	char c;
};
dr x[100010];
bool cmp(dr x,dr y){
	return x.x<y.x;
}
queue<int>q[200010];

signed main(){
	int t;
	cin>>t;
	while(t--){
		for(int i=0;i<=200000;i++) while(q[i].size()) q[i].pop();
		memset(a,0,sizeof(a));
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			dr b;
			int l;
			char c;
			cin>>b.x>>b.y>>l>>b.c;
			x[i]=b;
		}
		sort(x+1,x+n+1,cmp);
		int ans=0;
		for(int i=1;i<=n;i++){
			int p=x[i].x+x[i].y;
			if(x[i].c=='E') q[p].push(x[i].x);
			else{
				while(q[p].size() && q[p].front()+k<=x[i].x) q[x[i].x+x[i].y].pop();
				ans+=q[p].size(); 
			}
		}
		cout<<n*k-ans<<endl;
	}
	return 0; 
}



//N:y++
//E:x++
//x[i]+k==x[j] && y[i]==y[j]+k
//k==x[j]-x[i]==y[i]-y[j]
//if(x[i]+y[i]==y[j]+x[j])
/*
x
> 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 > 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 ^ 0 0
0 0 0 0 0 ^ 0
0 0 0 0 0 0 0 y
*/
