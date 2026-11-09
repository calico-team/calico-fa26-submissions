#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mp make_pair
const int N=1e5+20;

struct drone{
	ll x;
	ll y;
	ll height;
	char dir;
}a[N];

int n;
ll k;
vector <ll> edui[2*N],ndui[2*N];

map < pair <ll,ll> , int > q;

bool cmp2(drone X,drone Y){
	return X.height>Y.height;
}

bool cmp( pair <ll,char> X, pair <ll,char> Y ){
	return X.first<Y.first;
}

void solve(){
	ll lie,ans=0;
	q.clear();
	for(int i=2;i<=2*N;i++) edui[i].clear(),ndui[i].clear();
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y>>a[i].height;
		cin>>a[i].dir;
	}
	sort(a+1,a+n+1,cmp2);
	for(int i=1;i<=n;i++){
		lie=a[i].x+a[i].y;
		if( q[mp(a[i].x,a[i].y)]==0 ){
			if(a[i].dir=='N'){
				ndui[lie].push_back(a[i].x);
				q[mp(a[i].x,a[i].y)]=1;
			}else{
				edui[lie].push_back(a[i].x);
				q[mp(a[i].x,a[i].y)]=2;
			}
		}else if( q[mp(a[i].x,a[i].y)]==1 ){
			if(a[i].dir=='E'){
				edui[lie].push_back(a[i].x);
				q[mp(a[i].x,a[i].y)]+=2;
			}
		}else if( q[mp(a[i].x,a[i].y)]==2 ){
			if(a[i].dir=='N'){
				ndui[lie].push_back(a[i].x);
				q[mp(a[i].x,a[i].y)]+=1;
			}
		}
	}
	int sz1,sz2;
	for(int i=2;i<=2*N;i++){
		sz1=int(edui[i].size()),sz2=int(ndui[i].size());
		if(sz1==0 && sz2==0){
			continue;
		}
		if(sz1==0 || sz2==0){
			if(sz1==0){
				ans+=k*sz2;
			}else{
				ans+=k*sz1;
			}
			//continue;
		}
		if(edui[i].size()!=0 && ndui[i].size()!=0){
			sort(edui[i].begin(),edui[i].end());
			sort(ndui[i].begin(),ndui[i].end());
			ll tx;
			for(int j=0;j<sz1;j++){
				tx=edui[i][j];
				if(ndui[i][sz2-1]<tx){
					ans+=k;
				}else{
					int pr=upper_bound(ndui[i].begin(),ndui[i].end(),tx+k-1)-ndui[i].begin();
					int pl=lower_bound(ndui[i].begin(),ndui[i].end(),tx)-ndui[i].begin();
					//cout<<tx<<" "<<pl<<" "<<pr<<endl;
					ans+=k-(pr-pl);
				}
			}
			ans+=k*sz2;
		} 
		//cout<<ans<<endl;
	}
	cout<<ans<<'\n';
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
