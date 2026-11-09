#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n;
vector<ll> v[301100];
ll jz[301100];
void dfs(ll now,ll fa){
	jz[now]=fa;
	jz[1]^=fa;
	for(ll i=0;i<v[now].size();i++){
		if(v[now][i]==fa)continue;
		dfs(v[now][i],now);
	}
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin>>s;
	if(s=="FIRST"){
		cin>>n;
		for(ll i=1;i<=n;i++)jz[i]=0,v[i].clear();
		for(ll i=1;i<n;i++){
			ll a,b;
			cin>>a>>b;
			v[a].push_back(b);
			v[b].push_back(a);
		}
		dfs(1,0);
		for(ll i=1;i<=n;i++)cout<<jz[i]<<" ";
	}
	else{
		ll n;
		cin>>n;
		ll jk=0;
		for(ll i=1;i<=n;i++){
			cin>>jz[i];
			if(jz[i]!=-1&&i!=1){
				cout<<jz[i]<<" "<<i<<endl;
				jz[1]^=jz[i];
			}
			if(jz[i]==-1)jk=i;
		}
		if(jk==1)return 0;
		cout<<jz[1]<<" "<<jk<<endl;
	}
	return 0;
}
