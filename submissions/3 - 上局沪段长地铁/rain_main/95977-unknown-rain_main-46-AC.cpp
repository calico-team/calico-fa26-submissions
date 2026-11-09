#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct z{
	bool tp;
	ll x,y,z;
}wrj[503305];
ll n,k;
vector<ll> v[503305];
ll erf(ll i,ll mb){
	if(v[i].size()==0)return 0;
	ll l=0,r=v[i].size()-1,ans=v[i].size();
	while(l<=r){
		ll mid=(l+r)/2;
		if(v[i][mid]<mb){
			l=mid+1;
		}
		else{
			r=mid-1;
			ans=mid;
		}
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll T;
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(ll i=0;i<=2*100000;i++)v[i].clear();
		for(ll i=1;i<=n;i++){
			cin>>wrj[i].x>>wrj[i].y>>wrj[i].z;
			char c;
			cin>>c;
			if(c=='N'){
				ll jl=wrj[i].x+wrj[i].y;
				v[jl].push_back(wrj[i].x);
				wrj[i].tp=1;
			}
			else wrj[i].tp=0;
		}
		ll ans=n*k;
		for(ll i=0;i<=2*100000;i++)sort(v[i].begin(),v[i].end());
		for(ll i=1;i<=n;i++){
			if(wrj[i].tp==1)continue;
			ll jl=wrj[i].x+wrj[i].y;
			ans-=erf(jl,wrj[i].x+k)-erf(jl,wrj[i].x);
		}
		cout<<ans<<endl;
	}
	return 0;
}
