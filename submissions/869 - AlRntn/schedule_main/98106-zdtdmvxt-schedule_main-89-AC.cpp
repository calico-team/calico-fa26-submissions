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
  int32_t tc;
  std::cin >> tc;
  while(tc--){
    int64_t N,M,K;
    cin>>N>>M>>K;
    std::vector<std::vector<int64_t>>adj(N+1);
    std::vector<int64_t>par(N+1);
    for(int64_t i=1;i<=N;i++){
      int64_t p;
      cin>>p;
      adj[p].push_back(i);
      par[i]=p;
    }
    std::vector<int64_t>sub(N+1,0);
    std::y_combinator([&](auto self,int64_t v)->void{
      sub[v]=1;
      for(auto &u:adj[v]){
        self(u);
        sub[v]+=sub[u];
      }
    })(0);
    std::set<std::pair<int64_t,int64_t>>ss;
    for(int64_t v=1;v<=N;v++){
      if(par[v]==0)ss.insert({sub[v],v});
    }
    debug(par,sub);
    int64_t res=0;
    while(M--){
      std::vector<int64_t>t;
      while((int64_t)t.size()<K&&(int64_t)ss.size()>0){
        t.push_back((*ss.rbegin()).second);
        ss.erase((*ss.rbegin()));
      }
      res+=(int64_t)t.size();
      debug(t,ss);
      for(auto &u:t){
        for(auto &c:adj[u]){
          ss.insert({sub[c],c});
        }
      }
    }
    cout<<res<<'\n';
  }
  return 0;
}