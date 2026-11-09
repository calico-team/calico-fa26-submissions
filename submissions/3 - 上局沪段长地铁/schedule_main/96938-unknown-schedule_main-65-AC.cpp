#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,k,c[100001],vis[100001],jcd[100001];
vector<int>v[100001],vj;
void dfs(ll ni){
	jcd[ni]=1;
	for(int i=0;i<v[ni].size();i++){
		dfs(v[ni][i]);
		jcd[ni]=max(jcd[ni],jcd[v[ni][i]]+1);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	ll t;
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		for(int i=0;i<=n;i++)v[i].clear(),vis[i]=jcd[i]=0;
		for(int i=1;i<=n;i++){
			cin>>c[i];
			v[c[i]].push_back(i);
		}
		dfs(0);
		multiset<pair<ll,ll> >st;
		multiset<pair<ll,ll> >::iterator it;
		for(int i=1;i<=n;i++){
			if(c[i]==0)st.insert(make_pair(-jcd[i],i));
		}
		ll ans=0;
		for(int i=1;i<=m;i++){
			vj.clear();
			ll jsz=min(k,(ll)st.size());
			while(jsz--){
				it=st.begin();
				ll ji=it->second;
				st.erase(it);
				vis[ji]=1;ans++;
				for(int j=0;j<v[ji].size();j++)vj.push_back(v[ji][j]);
			}
			for(int j=0;j<vj.size();j++){
				st.insert(make_pair(-jcd[vj[j]],vj[j]));
			}
		}
		cout<<ans<<endl;
	} 
	return 0;
} 
