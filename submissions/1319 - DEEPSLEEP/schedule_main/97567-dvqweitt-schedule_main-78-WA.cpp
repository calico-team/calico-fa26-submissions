#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>

using namespace std;

constexpr int N=1e4+5;
constexpr int G=205;

#define int long long 

int n,m,k;

struct node{
	int u,cnt;
	bool operator<(const node& o)const{
		return cnt<o.cnt;
	}
};
priority_queue<node>q;
vector<int>v[N];
int ans;
int fa[N];
int son[N];
int chs[N],cnt;

namespace tqy{
	inline void init(){
		cin>>n>>m>>k;
		ans=0;
		for(int i=1;i<=n;++i){
			son[i]=0;
			v[i].clear();
		}
		for(int i=1;i<=n;++i){
			cin>>fa[i];
			v[fa[i]].emplace_back(i);
			++son[fa[i]];
		}
		while(!q.empty()){
			q.pop();
		}
		for(int i=1;i<=n;++i){
			if(fa[i]==0){
				q.push(node{i,son[i]});
			}
		}
	}
	inline void solve(){
		while(!q.empty()&&m>0){
			int mx=0;
			cnt=0;
			while(mx<k&&!q.empty()){
				++mx;
				chs[++cnt]=q.top().u;
				q.pop();
			}
			--m;
			ans+=mx;
			for(int i=1;i<=cnt;++i){
				for(auto s:v[chs[i]]){
					q.push(node{s,son[s]});
				}
			}
		}
		cout<<ans<<'\n';
	}
}

signed main(){
	int T;
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>T;
	while(T--)tqy::init(),tqy::solve();
	return 0;
}