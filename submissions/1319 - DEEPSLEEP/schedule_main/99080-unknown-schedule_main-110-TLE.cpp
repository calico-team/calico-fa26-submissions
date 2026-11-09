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
vector<int>e[N];
int ans;
int fa[N];
int sz[N];
int chs[N],cnt;

void dfs(int u){
	sz[u] = 1;
	for (int v : e[u]){
		if (v == fa[u]) continue;
		dfs(v);
		sz[u] += sz[v];
	}
	return ;
}

namespace tqy{
	inline void init(){
		cin>>n>>m>>k;
		ans=0;
		for(int i=1;i<=n;++i){
			sz[i]=0;
			e[i].clear();
		}
		for(int i=1;i<=n;++i){
			cin>>fa[i];
			e[fa[i]].emplace_back(i);
		}
		dfs(0);
		while(!q.empty()){
			q.pop();
		}
		for(int i=1;i<=n;++i){
			if(fa[i]==0){
				q.push(node{i,sz[i]});
			}
		}
	}
	inline void solve(){
        if (m > n){ cout << n << "\n"; return ; }
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
				for(auto s:e[chs[i]]){
					q.push(node{s,sz[s]});
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