#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>

using namespace std;

constexpr int N=1e4+5;
constexpr int G=205;

#define int long long 

namespace IO{
	struct INID{INID(){ios::sync_with_stdio(false);cin.tie(nullptr);}};
	static INID INI_D;
	inline int gc(){return cin.rdbuf()->sbumpc();}
	inline void pc(char c){cout.rdbuf()->sputc(c);}
	template<typename T>inline void rd(T &x){
		x=0;int f=1,c=gc();
		while('0'>c||c>'9'){if(c=='-')f*=-1;c=gc();}
		while('0'<=c&&c<='9'){x=x*10+c-'0';c=gc();}
		x*=f;
	}template<typename T>inline void wt(T x){
		if(x<0)pc('-');
		static int d,tp,stk[40];tp=0;
		do{d=x%10;stk[++tp]=(d<0?-d:d)+'0';x/=10;}while(x);
		while(tp)pc(stk[tp--]);
	}
}using namespace IO;

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
		rd(n),rd(m),rd(k);
		if(m>n){
			wt(n),pc('\n');
			return;
		}
		ans=0;
		for(int i=1;i<=n;++i){
			sz[i]=0;
			e[i].clear();
		}
		for(int i=1;i<=n;++i){
			rd(fa[i]);
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
		wt(ans),pc('\n');
	}
}

signed main(){
	int T;
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	rd(T);
	while(T--)tqy::init(),tqy::solve();
	return 0;
}