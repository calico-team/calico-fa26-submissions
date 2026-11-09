#include "bits/stdc++.h"
#ifdef AlRntn
#include "debug.hpp"
#else
#define debug(...) void(0)
#define tstr(...) void(0)
#endif
namespace std {
// from https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun>
class y_combinator_t {
  Fun fun_;
public:
  template<class T>
  explicit y_combinator_t(T &&fun): fun_(std::forward<T>(fun)) {}

  template<class ...Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};
template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_t<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}
namespace std{
struct dsu_t{
  int64_t max_N;std::vector<int64_t> par;std::vector<int64_t> siz;
  void init(int64_t _n){
    max_N=_n;par.resize(max_N,0);siz.resize(max_N,0);
  }
  void add_size(){
    max_N++;
    par.push_back(0);
    siz.push_back(0);
  }
  void make_set(int64_t v){
    par[v]=v;
    siz[v]=1;
  }
  int64_t find_set(int64_t v){
    return (v == par[v] ? v : par[v]=find_set(par[v]));
  }
  bool union_sets(int64_t v, int64_t u){
    v=find_set(v);
    u=find_set(u);
    if(v==u){
      return 0;
    }
    if(siz[u] > siz[v]) std::swap(u, v);
    return siz[v] += siz[u], par[u]=v, 1;
  }
};
} // namespace std
int main(){
#ifdef AlRntn
freopen("inputf.in" , "r" , stdin); freopen("outputf.out" , "w" , stdout); freopen("errorf.out" , "w" , stderr);
#endif
  using namespace std;
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
  int32_t tc;
  std::cin >> tc;
  while(tc--){
    int64_t N;
    cin>>N;
    std::vector<int64_t>A(N);
    for(auto &a:A)cin>>a,a--;
    std::vector<int64_t>V(N);
    for(auto &v:V)cin>>v;
    struct trie{
      std::vector<std::array<int64_t,2>>ch;std::vector<int64_t> cnt;
      void init(){
        new_node();
      }
      void clear(){
        ch.clear();
        cnt.clear();
        ch.push_back({0,0});
        cnt.push_back(0);
      }
      int64_t new_node(){
        ch.push_back({0,0});
        cnt.push_back(0);
        return (int64_t)ch.size()-1;
      }
      void add(int64_t x,int64_t d){
        int64_t u=0;
        for(int64_t k=29;k>=0;k--){
          int64_t b=(x>>k)&1;
          if(!ch[u][b]){
            ch[u][b]=new_node();
          }
          u=ch[u][b]; cnt[u]+=d;
        }
      }
      int64_t ask(int64_t x){
        int64_t u=0,r=0;
        for(int64_t k=29;k>=0;k--){
          int64_t b=(x>>k)&1;
          int64_t w=ch[u][b^1];
          if(w&&cnt[w]>0){ 
            r^=(int64_t)(1<<k); 
            u=w;
          }else{
            u=ch[u][b];
          }
        }
        return r;
      }
    };
    std::dsu_t d;
    d.init(N);
    for(int64_t i=0;i<N;i++)d.make_set(i);
    std::vector<int64_t>res(N,-1),pos(N,-1),fcyc(N,-1),hei(N,0),par(N,-1),cyclen(N,0),cmp(N,-1);
    std::vector<bool>mark(N,0);
    int64_t idxx=0;
    auto dfs=std::y_combinator([&](auto self,int64_t v)->void{
      mark[v]=1;
      if(!d.union_sets(v,A[v])){
        int64_t idx=0;
        int64_t u=v;
        while(u!=A[v]){
          pos[u]=idx++;
          cmp[u]=idxx;
          fcyc[u]=u;
          u=par[u];
        }
        pos[A[v]]=idx++;
        cmp[A[v]]=idxx;
        u=v;
        while(u!=A[v]){
          cyclen[u]=idx;
          u=par[u];
        }
        cyclen[A[v]]=idx;
        fcyc[A[v]]=A[v];
        idxx++;
      }else{      
        if(!mark[A[v]]){
          par[A[v]]=v;
          self(A[v]);
        }
        if(pos[v]==-1){
          fcyc[v]=fcyc[A[v]];
          hei[v]=hei[A[v]]+1;
        }
      }
    });
    for(int64_t v=0;v<N;v++){
      if(!mark[v])dfs(v);
    }
    std::vector<bool>mark2(N,0);
    std::vector<std::vector<int64_t>>adj(N);
    for(int64_t v=0;v<N;v++){
      if(cmp[v]!=-1&&cmp[A[v]]!=-1)continue;
      adj[A[v]].push_back(v);
    }
    std::vector<int64_t>pref(N,0);
    for(int64_t v=0;v<N;v++){
      if(cmp[v]>-1&&!mark2[v]){
        debug(v);
        trie s;
        s.init();
        s.add(0,1);
        int64_t u=v,p=0;
        std::vector<int64_t>vv;
        while(!mark2[u]){
          pref[u]=p;
          s.add(p,1);
          p^=V[u];
          vv.push_back(u);
          mark2[u]=1;
          u=A[u];
        }
        debug(vv);
        for(int64_t i=0;i<(int64_t)vv.size();i++){
          s.add(p^pref[vv[i]],1);
        }
        debug(pref,vv);
        for(auto &r:vv){
          std::y_combinator([&](auto self,int64_t v,int64_t par=-1)->void{
            res[v]=s.ask(pref[v]);
            for(auto &u:adj[v]){
              if(u==par)continue;
              pref[u]=pref[v]^V[u];
              s.add(pref[u],1);
              self(u,v);
              s.add(pref[u],-1);
            }
          })(r);
        }
      }
    }
    for(int64_t i=0;i<N;i++)cout<<res[i]<<' ';
    cout<<'\n';
  }
  return 0;
}