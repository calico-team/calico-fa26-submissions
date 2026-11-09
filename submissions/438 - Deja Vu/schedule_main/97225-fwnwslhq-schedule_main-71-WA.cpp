#include "bits/stdc++.h"
using namespace std;
#define mod 1000000007
#define ll long long
#define ff first
#define ss second
#define pb push_back
#define N 24
#define maxn 200005
#define INF (int)1e9

bool b[maxn];
vector<int> v[maxn];

void solve(){
	int n,m,k;
	cin>>n>>m>>k;
	set<int> s;
	int pr[n+5];
	for(int i=1; i<=n; i++){
		cin>>pr[i];
		if(pr[i]!=0)v[pr[i]].pb(i);
	}
	int ans=0;
	for(int i=1; i<=n; i++){
		if(pr[i]==0)s.insert(i);
	}
	for(int i=1; i<=m; i++){
		if(s.empty())break;
		auto it=s.begin(),it2=s.begin();
		set<int> ms;
		int cnt=0;
		vector<int> dl;
		for(int j=1; j<=k; j++){
			if(it==s.end())break;
			bool d=false;
			while(true){
				if(it==s.end())break;
				int x=(*it);
				int p=0;
				for(auto u:v[x]){
					if(!b[u]){
						b[u]=true;
						ms.insert(u);
						p++;
					}
				}
				if(p>0){
					dl.pb((*it));
					it++;
					d=true;
					break;
				}
				it++;
			}
			if(d)ans++,cnt++;
			else break;
		}
		for(int j=0; j<dl.size(); j++){
			s.erase(dl[j]);
		}
		dl.clear();
		it=s.begin();
		while(cnt<k){
			if(it==s.end())break;
			int x=(*it);
			dl.pb(*it);
			ans++;
			it++;
			cnt++;
		}
		for(int j=0; j<dl.size(); j++){
			s.erase(dl[j]);
		}
		for(int j=1; j<=k; j++){
			auto it2=s.begin();
			if(it==it2)break;
			else s.erase(it2);
		}
		auto it1=ms.begin();
		while(it1!=ms.end()){
			s.insert((*it1));
			it1++;
		}
	}
	cout<<ans<<'\n';
	for(int i=1; i<=n; i++)b[i]=0,v[i].clear();
}
 
int main(){
	// freopen("in.txt","w",stdout);
	// freopen("out.txt","r",stdin);
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll t=1;
	cin>>t;
	while(t--) solve();
}