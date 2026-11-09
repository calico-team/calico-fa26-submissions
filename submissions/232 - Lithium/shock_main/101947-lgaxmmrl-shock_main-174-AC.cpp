#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll t,n,m,q;
ll x[20005],y[20005],p[20005];
vector<ll> ans[1000005];
set<ll> rem[1000005];
ll dis(ll u,ll v,ll a,ll b){
	return (u-a)*(u-a)+(v-b)*(v-b);
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>q;
		for(int i=1;i<=n;i++) ans[i].clear(),ans[i].push_back(0);
		for(int i=1;i<=q;i++)
			cin>>x[i]>>y[i]>>p[i],x[i]++,y[i]++;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				rem[i].insert(j),ans[i].push_back(0);
		for(int i=q;i>=1;i--){
//			cout<<"shake: "<<x[i]<<' '<<y[i]<<' '<<p[i]<<endl;
			for(int j=max(x[i]-p[i],1ll);j<=min(x[i]+p[i],n);j++){
//				cout<<"x= "<<j<<endl;
				int k1=ceil(-sqrt(p[i]*p[i]-(j-x[i])*(j-x[i])));
				int k2=-k1;
				k1+=y[i];
				k2+=y[i];
//				cout<<"range "<<k1<<" to "<<k2<<endl;
				set<ll>::iterator it=rem[j].lower_bound(k1);
				vector<ll> v;
				for(it;it!=rem[j].end();it++){
					if(*it>k2) break;
					v.push_back(*it);
	//				cout<<*it<<" deleted\n";
					ans[j][*it]=p[i]*p[i]-dis(j,*it,x[i],y[i])+1;
				}
				for(auto vv:v) rem[j].erase(rem[j].find(vv));
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++) cout<<ans[i][j]<<' ';
			cout<<endl;
		}
	}
	return 0;
}