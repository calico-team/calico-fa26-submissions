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
int main(){
#ifdef AlRntn
freopen("inputf.in" , "r" , stdin); freopen("outputf.out" , "w" , stdout); freopen("errorf.out" , "w" , stderr);
#endif
  using namespace std;
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
  std::string S;
  cin>>S;
  if(S=="FIRST"){
    int64_t N;
    cin>>N;
    std::vector<std::vector<int64_t>>adj(N+1);
    for(int64_t i=0;i+1<N;i++){
      int64_t u,v;
      cin>>u>>v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    std::vector<int64_t>p(N+1,-1);
    std::y_combinator([&](auto self,int64_t v)->void{
      for(auto &u:adj[v]){
        if(u==p[v])continue;
        p[u]=v;
        self(u);
      }
    })(1);
    p[1]=0;
    for(int64_t i=2;i<=N;i++)p[1]^=p[i];
    for(int64_t i=1;i<=N;i++){
      cout<<p[i]<<' ';
    }
    cout<<'\n';
  }else{
    int64_t N;
    cin>>N;
    std::vector<int64_t>p(N+1,-1);
    for(int64_t i=1;i<=N;i++)cin>>p[i];
    if(p[1]==-1){
      for(int64_t i=2;i<=N;i++){
        cout<<i<<' '<<p[i]<<'\n';
      }
    }else{
      for(int64_t i=2;i<=N;i++){
        if(p[i]>-1)p[1]^=p[i];
      }
      for(int64_t i=2;i<=N;i++){
        if(p[i]==-1)p[i]=p[1];
      }
      for(int64_t i=2;i<=N;i++){
        cout<<i<<' '<<p[i]<<'\n';
      }
    }
  }
  return 0;
}