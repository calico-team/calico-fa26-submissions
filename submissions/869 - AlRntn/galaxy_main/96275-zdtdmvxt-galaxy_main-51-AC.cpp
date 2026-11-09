#include "bits/stdc++.h"
#ifdef AlRntn
#include "debug.hpp"
#else
#define debug(...) void(0)
#define tstr(...) void(0)
#endif
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
    int64_t N,M,Q;
    cin>>N>>M>>Q;
    std::dsu_t d;
    d.init(N*M);
    for(int64_t i=0;i<N;i++){
      for(int64_t j=0;j<M;j++)d.make_set(i*M+j);
    }
    std::vector<std::string>G(N);
    for(auto &g:G)cin>>g;
    for(int64_t i=0;i<N;i++){
      for(int64_t j=0;j<M;j++){
        std::vector<int64_t>dx={1,-1,0,0};
        std::vector<int64_t>dy={0,0,1,-1};
        for(int64_t x=0;x<4;x++){
          auto ni=i+dx[x];
          auto nj=j+dy[x];
          if(0<=ni&&ni<N&&0<=nj&&nj<M){
            if(G[i][j]=='.'||G[ni][nj]=='.'){
              d.union_sets(i*M+j,ni*M+nj);
            }else if(G[i][j]==G[ni][nj]){
              d.union_sets(i*M+j,ni*M+nj);
            }
          }
        }
      }
    }
    while(Q--){
      int64_t x1,y1,x2,y2;
      cin>>x1>>y1>>x2>>y2;
      if(d.find_set(x1*M+y1)==d.find_set(x2*M+y2))cout<<"YES\n";
      else cout<<"NO\n";
    }
  }
  return 0;
}