#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,q,p[100001],x[100001],y[100001];
vector<int>v[1000001],bcj[1000001];
ll cx(ll jx,ll jy){
	if(bcj[jx][jy]==jy)return jy;
	return bcj[jx][jy]=cx(jx,bcj[jx][jy]);
}
ll pf(ll jx){
	return jx*jx;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	ll t;
	cin>>t;
	while(t--){
		cin>>n>>m>>q;
		for(int i=1;i<=n;i++){
			v[i].clear();bcj[i].clear();
			bcj[i].push_back(0);v[i].push_back(0);
			for(int j=1;j<=m;j++){
				v[i].push_back(0);
				bcj[i].push_back(j);
			}
			bcj[i].push_back(m+1);
		}
		for(int i=1;i<=q;i++)cin>>x[i]>>y[i]>>p[i];
		for(int i=q;i>=1;i--){
			x[i]++;y[i]++;
			for(int jx=max(1ll,x[i]-p[i]);jx<=min(n,x[i]+p[i]);jx++){
				for(int jy=max(1ll,y[i]-p[i]);jy<=min(m,y[i]+p[i]);jy++){
					if(cx(jx,jy)!=jy){
						jy=cx(jx,jy)-1;
						continue;
					}
					v[jx][jy]=max(0ll,pf(p[i])-(pf(jx-x[i])+pf(jy-y[i]))+1);
					if(v[jx][jy]!=0)bcj[jx][jy]=jy+1;
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)cout<<v[i][j]<<" ";
			cout<<endl;
		}
	} 
	return 0;
} 
